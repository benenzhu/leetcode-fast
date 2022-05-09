// ==UserScript==
// @name         leetcode复制代码
// @namespace    http://tampermonkey.net/
// @version      0.1
// @description  try to take over the world!
// @author       You
// @match        https://leetcode.cn/problems/*
// @match        https://leetcode-cn.com/problems/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=leetcode-cn.com
// @grant        GM_setClipboard
// ==/UserScript==



(function () {
    'use strict';

    addButton('copycode', selectReadFn)


    function addButton(text, onclick, cssObj) {
     cssObj = cssObj || {position: 'absolute', bottom: '0%', left:'70%', 'z-index': 3}
     let button = document.createElement('button'), btnStyle = button.style
     document.body.appendChild(button)
     button.id = "copy_code"
     button.innerHTML = text
     button.onclick = onclick
     Object.keys(cssObj).forEach(key => btnStyle[key] = cssObj[key])
     return button
    }

    function selectReadFn() {
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
        out +="\n\n\n\n"
        var dd = document.getElementsByClassName("view-lines monaco-mouse-cursor-text")[0].innerText.split("\n");
        for(i = 0; i<dd.length; i++){out+=(dd[i].replace(/[^\x00-\x7F]/g, " ")+"\n")}
        console.log(out)
        GM_setClipboard(out)
        document.getElementById("copy_code").innerText = "copyed"
    }




})();