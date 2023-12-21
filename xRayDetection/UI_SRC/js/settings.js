


window.onload = function () { 
    var urlParams = new URLSearchParams(window.location.search);
    var selectedParam = urlParams.get('selected');  //获取发送过来的模型名字

    console.log(selectedParam); // 输出所选项的值：模型名字

    let lefttime_text = document.querySelector(".lefttime_text ul")
    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function () {
        if (xhr.status === 200 && xhr.readyState === 4) {
            let res = JSON.parse(xhr.responseText)

            let data_type = res.args.label
            for (let i = 0; i < data_type.length; i++) {
                li = document.createElement("li")
                li.innerHTML = data_type[i]
                li.classList.add("bg")
                li.classList.add("active")
                lefttime_text.appendChild(li)
            }
            for (let i = 0; i < lefttime_text.children.length; i++) {
                lefttime_text.children[i].onclick = function () {

                    lefttime_text.children[i].classList.toggle("active")
                }
            }
        }
    }
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "SwitchModel");
    xhr.setRequestHeader("ModelName", selectedParam);
    xhr.send()


};





let ind=document.querySelector(".ind")
let sta=document.querySelector(".sta")
ind.onclick=function(){
    passSelectedValue('index',ind)
}
sta.onclick=function(){
    passSelectedValue('statistics',sta)
}
function passSelectedValue(hrefs,obj) {


                    // 	 // 获取选择框元素
    var urlParams = new URLSearchParams(window.location.search);
    var selectedParam = urlParams.get('selected');

   

    let href_lj=''
        if(hrefs=='index'){
            href_lj=`${hrefs}.html?selected=${selectedParam}&back=${background_color}`
        }else if(hrefs=='statistics'){
            href_lj=`${hrefs}.html?selected=${selectedParam}&back=${background_color}`
        }
// 构建带有查询参数的新链接地址
    // var newLink = href_lj+ selectedParam;

// 修改跳转链接为新链接地址
    console.log(href_lj);
    obj.href=href_lj




    // 提交设置




    // let confidence_sub = document.querySelector("#confidence")
    // let accuracy_sub = document.querySelector("#accuracy")
    // let xhr = new XMLHttpRequest()
    // xhr.onreadystatechange = function () {
    //     if (xhr.status === 200 && xhr.readyState === 4) {
    //         let res = JSON.parse(xhr.responseText)
    //         console.log(res);
    //         // label= res.args.label
    //         // statistics = res.args.statistics
            
    //     }
    // }
    // xhr.open("get", `http://localhost:7899/QueryData`)
    // xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    // xhr.setRequestHeader("cmd", "UpdateSettings");
    // xhr.setRequestHeader("confidence", confidence_sub.value);
    // xhr.setRequestHeader("iou", accuracy_sub.value);
    // xhr.setRequestHeader("BoxColor", color);
    // xhr.setRequestHeader("BoxLineSize", value);
    // xhr.send()






}











    




// setup 滑杆




(function () {








    











})();
