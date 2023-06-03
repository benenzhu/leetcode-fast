/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <algorithm>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "hdfs.h"
#include "helloworld.pb.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <etcd/Client.hpp>
#include <etcd/Response.hpp>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "ModelSliceReader.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif
using namespace std;
using alimama::proto::ModelService;
using alimama::proto::Request;
using alimama::proto::Response;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

map<long long, pair<long long, string>> model_meta_name;

map<long long, pair<long long, string>> model_data;

#define log(msg) std::cout << __LINE__ << "->  " << msg << std::endl

constexpr int PATHSIZE = 20;

using namespace std;

vector<string> split(std::string param, char seg = '\n') {
  vector<string> arr;
  std::string temp = "";
  for (auto it = param.begin(); it != param.end(); it++) {
    if (*it == seg) {
      arr.push_back(temp);
      temp = "";
    } else {
      temp += *it;
    }
  }
  arr.push_back(temp);
  return std::move(arr);
}

inline int command(string s) { return system(s.c_str()); }

inline int hdfsDownload(string path, string local_path) {
  log("download " << path << " to " << local_path);
  return 1;
  return command("hdfs dfs -fs hdfs://namenode:9000/ -get -f " + path + " " +
                 local_path);
}

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public ModelService::Service {
  Status Get(ServerContext *context, const Request *request,
             Response *response) override {
    log("receive request");
    string s = "";
    auto A = ModelSliceReader();
    auto reqdata = std::chrono::steady_clock::now();
    for (int j = 0; j < request->slice_request_size(); j++) {
      auto i = request->slice_request(j);
      auto slice_partition = i.slice_partition();
      auto data_start = i.data_start();
      auto data_len = i.data_len();

      /* auto it = model_meta_name.upper_bound(data_start); */
      auto it = model_data.upper_bound(data_start);
      --it;
      while (data_len > 0) {

        auto file_start = it->first;
        auto file_end = it->second.first;
        auto file_name = it->second.second;
        int read_pos = data_start - file_start;
        int read_len = min((unsigned long long)data_len, file_end - data_start);
        if (read_len) {
          // log(read_pos << " " << read_len);
          int start = s.size();
          s.resize(s.size() + read_len);
          memcpy((void *)(s.c_str() + start), file_name.c_str() + read_pos,
                 read_len);
        }
        data_start += read_len;
        data_len -= read_len;
        it++;
        /*
          auto file_start = it->first;
          auto file_end = it->second.first;
          auto file_name = it->second.second;
          int read_pos = data_start;
          int read_len = min((unsigned long long)data_len, file_end -
          data_start); if (read_len) {
            // log(read_pos << " " << read_len);
            A.Load(file_name);
            int start = s.size();
            s.resize(s.size() + read_len);
            A.Read(read_pos, read_len, (char *)(s.c_str() + start));
            A.Unload();
          }
          data_start += read_len;
          data_len -= read_len;
          it++;
        */
      }
      if (j % 500 == 0) {
        log(j);
      }
      // log("finished one");
    }

    response->set_status(0);
    log("s.size ::" << s.size());
    response->add_slice_data(s);
    auto reqdataend = std::chrono::steady_clock::now();

    double time =
        std::chrono::duration<double, std::milli>(reqdataend - reqdata).count();
    log("all done" << time);

    return Status::OK;
  }
};

int LoadModel() {

  hdfsFS fs = hdfsConnect("hdfs://namenode:9000", 0);

  int num_files = 0;
  std::string hdfs_path = "/backup/";
  hdfsFileInfo *file_info =
      hdfsListDirectory(fs, hdfs_path.c_str(), &num_files);

  if (!file_info) {
    cerr << "Failed to list directory: " << hdfs_path << endl;
    hdfsDisconnect(fs);
    return 1;
  }

  // getmaxPath
  string target_path = "";
  for (int i = 0; i < num_files; i++) {
    if (file_info[i].mKind == kObjectKindDirectory) {
      string path_name = file_info[i].mName + PATHSIZE;
      log("file_name: " << path_name);
      string done_path = path_name;
      done_path += "/model.done";
      if (hdfsExists(fs, done_path.c_str()) == 0) {
        if (target_path == "" || path_name > target_path) {
          target_path = path_name;
        }
      }
    }
  }

  log("find max path: " << target_path);

  /* if(hdfsCopy(fs, path.c_str(), local) != 0){ */
  /**/
  /* } */

  hdfsFreeFileInfo(file_info, num_files);

  string model_meta_path = target_path + "/model.meta";

  char *buffer = new char[10000];
  memset(buffer, 0, 10000);

  auto readFile =
      hdfsOpenFile(fs, model_meta_path.c_str(), O_RDONLY, 10000, 10000, 10000);
  if (!readFile) {
    log("Fail");
  }
  auto tSize = hdfsRead(fs, readFile, (void *)buffer, 10000);
  if (tSize < 0) {
    log("Fail");
  }
  hdfsCloseFile(fs, readFile);

  auto lines = split(buffer);
  log(lines.size());
  for (auto &i : lines) {
    log(i);
  }

  int start_size = 0;

  auto parseMeta = [&]() {
    long long start = 0;
    for (auto &i : lines) {
      if (i.size() > 10 && i[0] == 's') {
        auto vec = split(i, ':');
        auto name = split(vec[1], ',')[0];
        int size = stoi(vec[vec.size() - 1]);

        string remote_path = target_path + "/" + name;

        hdfsDownload(remote_path, ".");
        model_meta_name[start] = {start + size, name}; // 这里不减了
        start += size;
      }
    }
  };

  parseMeta();

  for (auto &i : model_meta_name) {
    auto k = i.first;
    auto end = i.second.first;
    auto name = i.second.second;
    log(k << " " << end << " " << name);

    model_data[k] = {end, ""};
    string &data = model_data[k].second;
    data.resize(end - k + 1);
    auto A = ModelSliceReader();
    A.Load(name);
    A.Read(0, end - k + 1, (char *)data.c_str());
    A.Unload();
  }
  return 0;
}

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening" << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

std::string getLocalIP() {
  struct ifaddrs *ifAddrStruct = NULL;
  void *tmpAddrPtr = NULL;
  std::string localIP;
  getifaddrs(&ifAddrStruct);
  while (ifAddrStruct != NULL) {
    if (ifAddrStruct->ifa_addr->sa_family == AF_INET) {
      tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
      char addressBuffer[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
      std::string interfaceName(ifAddrStruct->ifa_name);
      if (interfaceName == "en0" || interfaceName == "eth0") {
        return addressBuffer;
      }
    }
    ifAddrStruct = ifAddrStruct->ifa_next;
  }
  return "";
}

void registerServer() {

  std::string local_ip = getLocalIP();
  std::string external_address =
      local_ip + std::string(":") + std::to_string(50051);
  etcd::Client etcd("http://etcd:2379");
  std::string key = std::string("/services/modelservice/") + external_address;
  std::string value("");
  etcd.set(key, value);
}

int main(int argc, char **argv) {

  LoadModel();

  registerServer();

  RunServer();

  return 0;
}
