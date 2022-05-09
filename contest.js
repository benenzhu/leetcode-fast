// ==UserScript==
// @name         leetcode周赛
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  try to take over the world!
// @author       You
// @match        https://leetcode.cn/contest/*
// @match        https://leetcode-cn.com/contest/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=leetcode-cn.com
// @grant        GM_setClipboard
// ==/UserScript==



(function () {
    'use strict';
    //window.addEventListener('load',() => {
    //
    //})

    function addButton(text, onclick, cssObj) {
     cssObj = cssObj || {position: 'absolute', top: '0%', left:'30%', 'z-index': 3}
     let button = document.createElement('button'), btnStyle = button.style
     document.body.appendChild(button)
     button.id = "copy_code"
     button.innerHTML = text
     button.onclick = onclick
     Object.keys(cssObj).forEach(key => btnStyle[key] = cssObj[key])
     return button
    }
    var num = 0
    function selectReadFn() {
        document.getElementById("copy_code").innerText = "wait sec"
        var out = ""
        var a = document.getElementsByTagName("pre");
        for(var i = 0; i < a.length;i++){
            if(a[i].innerHTML.search("输入") > 0){
                var c = a[i].innerText;
                c = c.split("\n");
                out+=('//'+c[0]+"\n")
                out+=('//'+c[1]+"\n")
            }
        }
        out +="\n\n"
        var dd = document.getElementsByClassName("CodeMirror-code")[0].innerText.split("\n");
        for(i = 1; i<dd.length; i+=2){out+=(dd[i].replace(/[^\x00-\x7F]/g, " ")+"\n")}
        console.log(out)
        GM_setClipboard(out)
        num += 1
        document.getElementById("copy_code").innerText = "copyed" + num
    }
    addButton('copycode', selectReadFn)
})();