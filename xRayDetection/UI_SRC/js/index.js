

let con = document.querySelector(".conversion")
let mainbox = document.querySelector(".mainbox")
let menu = document.querySelector(".menu")
let updata_name_src = {}   //更新页面名字 图片地址列表  name:src

setTimeout(() => {
    for (let i = 0; i < mainbox.children.length; i++) {
        mainbox.children[i].style.display = 'none'
    }
    mainbox.children[0].style.display = "block"
}, 2000)


let bla_name = 0

//默认index样式
con.children[0].classList.add("change_be")
con.children[0].classList.add("change_af")
con.children[0].children[0].classList.add("change_be")
con.children[0].children[0].classList.add("change_af")
con.children[0].children[0].style.color = '#f4e925'


//点击切换界面
con.onclick = function (e) {
    if (e.target.nodeName.toLowerCase() == 'a') {

        // 重置样式
        for (let c = 0; c < con.children.length; c++) {
            con.children[c].classList.remove("change_be")
            con.children[c].classList.remove("change_af")
            con.children[c].children[0].classList.remove("change_be")
            con.children[c].children[0].classList.remove("change_af")
            con.children[c].children[0].style.color = '#fff'
        }


        for (let i = 0; i < mainbox.children.length; i++) {
            // console.log(mainbox.children[i]);
            if (mainbox.children[i].getAttribute("name") == e.target.name) {
                e.target.classList.add("change_be")
                e.target.classList.add("change_af")
                e.target.parentNode.classList.add("change_be")
                e.target.parentNode.classList.add("change_af")
                e.target.style.color = "#f4e925"



                mainbox.children[i].style.display = 'block'
                if (e.target.name == 'settings') {
                    bla_name = 1

                } else {

                    if (bla_name == 1) {
                        settingsupdata()

                    }
                    bla_name = 0
                }

                if (e.target.name == 'update') {
                    updata_name_src = {}  //清空

                }

            } else {
                mainbox.children[i].style = ''
                mainbox.children[i].style.display = 'none'
            }
        }

    }
}














var appNamelist = document.querySelector("#selectElem")
appNamelist.remove(0)
appNamelist.disabled = "true"
// option.disabled
let body = document.querySelector("body")

// // 切换模型    全局
var label = []   //类别
var statistics = []  //数量 key:value



var DetectedItem = []   //存储违禁物品信息 即使更换模型也不重置 除关闭程序

var flages = 0   //有违禁物品就是1  反之0




window.onload = function () {


    // ani  切换模型等待加载    以及首先进入的加载

    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function () {
        if (xhr.status === 200 && xhr.readyState === 4) {
            let res = JSON.parse(xhr.responseText)
            let model = res.args.ModelNames

            for (let i = 0; i < model.length; i++) {
                let option = document.createElement("option")
                option.value = model[i]
                option.innerHTML = model[i]
                appNamelist.appendChild(option)

            }
            LoadModel();
        }
    }
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "Init");
    xhr.send();

    //setTimeout(LoadModel, 2000)
};














// 动画  
var ani = document.querySelector(".ani")
setTimeout(() => {
    ani.style.transition = '1s'
    ani.style.opacity = 0
    setTimeout(() => {
        ani.style.display = 'none'

    }, 1000)
}, 3000);








// 警告
let vi_back = document.querySelector(".vi_back")


// 是否有违禁物品显示相应图片
let tds = document.querySelector(".tds")



//违禁物品信息
let statusList = document.querySelectorAll(".statusList")

//违禁物品截图
let right_top = document.querySelector(".right_top");


let timers = null  //实时

// update
let box_update_le_ul = document.querySelector(".box_update_le ul")

// update
let update_box_ul = document.querySelector(".update_box ul")


//模型选择 
var sortedStatistics = null
var titlename = []
var titlenum = []

let data_pie = []   //统计

let box_type_name = []

LoadModel = function () {
    let ModelName = "";

    if (appNamelist.children[0].value != "") {
        ModelName = appNamelist.children[0].value
    }
    else {
        ModelName = appNamelist.children[1].value
    }
    //let ModelName = appNamelist.children[0].value


    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function () {
        if (xhr.status === 200 && xhr.readyState === 4) {
            let res = JSON.parse(xhr.responseText)

            label = res.args.label
            statistics = res.args.statistics

            // 违禁物品类别   数据    主页面和设置界面
            sortedStatistics = Object.entries(statistics).sort((a, b) => b[1] - a[1]); //用于主页面和统计界面

            //    进行排序分割  //用于主页面和统计界面

            titlename = []
            titlenum = []
            for (let n = 0; n < sortedStatistics.length; n++) {
                titlename[n] = sortedStatistics[n][0]
                titlenum[n] = sortedStatistics[n][1]
            }
            box_type_name = titlename
            while (titlename.length < 8) {
                box_type_name.push("1")
                titlenum.push(0)
            }

            data_type()

            // 统计界面  制作数据
            data_pie = []
            for (let p = 0; p < titlename.length; p++) {
                data_pie[p] = { "name": titlename[p], "value": titlenum[p] }
            }

            // mainbox.children[2].style.display="block"
            echarts_1()
            echarts_3()
            // mainbox.children[2].style.display="none"
            click_effect()

        }


    }
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "SwitchModel");
    xhr.setRequestHeader("ModelName", ModelName);
    xhr.send()

    clearInterval(timers)
    ju_model(ModelName)



};



// var filter=null  //过滤

//点击类别事件效果 两个分别是主界面和设置    之后过滤
let lefttime_text = document.querySelectorAll(".lefttime_text ul")

function click_effect() {
    for (let g = 0; g < lefttime_text.length; g++) {
        for (let d = 0; d < lefttime_text[g].children.length; d++) {
            lefttime_text[g].children[d].onclick = function () {
                lefttime_text[0].children[d].classList.toggle("active")
                lefttime_text[1].children[d].classList.toggle("active")
                // filter=lefttime_text[g].children[d].innerHTML
            }
        }
    }
}


function echarts_2() {

    sortedStatistics = Object.entries(update_echarts).sort((a, b) => b[1] - a[1]);

    titlename = []
    titlenum = []
    for (let n = 0; n < sortedStatistics.length; n++) {
        titlename[n] = sortedStatistics[n][0]
        titlenum[n] = sortedStatistics[n][1]
    }
    box_type_name = titlename
    while (titlename.length < 8) {
        box_type_name.push("1")
        titlenum.push(0)
    }

    // 基于准备好的dom，初始化echarts实例   左下
    var myChart = echarts.init(document.getElementById('echart2'));

    option = {
        grid: {
            left: '0%',
            top: '0',
            right: '20%',
            bottom: '0%',
            containLabel: true
        },
        xAxis: {
            show: false
        },
        yAxis: [{
            show: true,
            data: box_type_name,
            inverse: true,
            animationDuration: 300,
            animationDurationUpdate: 300,

            axisLabel: {

                textStyle: {
                    color: '#fff'
                },
            },

        }, {
            // 限制不要超出
            show: false,

            data: titlenum,

            axisLabel: { textStyle: { color: '#fff' } },

        }
        ],
        dataZoom: [{   //滚动体
            type: 'slider',
            yAxisIndex: 0,
            startValue: 0, // 数据窗口范围的起始数值
            endValue: 5, // 数据窗口范围的结束数值（可以根据需要进行调整）


        }],
        series: [{
            realtimeSort: true,

            name: '条',
            type: 'bar',
            data: titlenum,
            barWidth: '30px',
            // barGap: '5%',
            // barCategoryGap:"10px",
            itemStyle: {
                normal: {
                    barBorderRadius: 40,
                    color: '#1089E7',
                },
            },
            // 柱子上数据
            label: {
                normal: {
                    show: true,
                    position: 'right',
                    formatter: '{c}',
                    textStyle: { color: 'rgba(255,255,255,1)' }
                }
            },
        },],

    };
    // 使用刚指定的配置项和数据显示图表。
    myChart.setOption(option);
    window.addEventListener("resize", function () {
        myChart.resize();
    });
}

update_echarts = {}

var data_type = function () {

    var data_type = label

    for (let l = 0; l < data_type.length; l++) {
        update_echarts[data_type[l]] = 0
    }

    // 类别
    for (let g = 0; g < lefttime_text.length; g++) {
        while (lefttime_text[g].firstChild) {  //清空
            lefttime_text[g].removeChild(lefttime_text[g].firstChild);
        }

        for (let i = 0; i < data_type.length; i++) {
            li = document.createElement("li")
            li.innerHTML = data_type[i]
            li.classList.add("bg")
            li.classList.add("active")
            lefttime_text[g].appendChild(li)
        }
    }

    // 统计
    echarts_2()
};

data_type();









// 判断是否有违禁物   显示对应图片      
function warn() {
    let img = ""
    if (flages == 1) {
        img = 'img/false.png'  //  true   false medium 切换  

        tds.classList.add("tds_add")

    } else if (flages == 0) {
        img = 'img/true.png'

        tds.classList.remove("tds_add")

    }
    tds.children[0].src = img
};


function remove_cla() {
    for (let r = 0; r < statusList[1].children.length; r++) {
        statusList[1].children[r].classList.remove("add_info_main")

    }
    for (let r = 0; r < right_top.children.length; r++) {
        right_top.children[r].classList.remove("add_info_main")
    }
}

let bor_color = 'red'
let bor_value = 1
let img_width = 0   //原始图片的宽度
let img_height = 0  //原始图片的高度
let width_ratio = 0  //原始图片与控件的宽度比值
let height_ratio = 0  //原始图片与控件的高度比值

setTimeout(() => {

}, 1500)


// 实时发送请求 获取  OriginalImage DetectedItem 以及更新 违禁物品数量

function r_time() {
    console.log(123);
    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function () {
        if (xhr.status === 200 && xhr.readyState === 4) {
            if (xhr.responseText != "") {

                let res = JSON.parse(xhr.responseText)
                if (res) {  //有数据

                    let ba_matrix = []  //矩阵重置
                    if (res.args.DetectedItem.length != 0) {  //违禁物品信息添加
                        flages = 1;   //显示 true  medine false
                        let uls = document.createElement('ul')
                        for (let i = 0; i < res.args.DetectedItem.length; i++) {

                            update_echarts[res.args.DetectedItem[i].label] += 1


                            let ul = document.createElement('ul')
                            DetectedItem.push(res.args.DetectedItem[i])
                            let date = new Date()
                            ul.classList.add("add_info")
                            let id = document.createElement("li")
                            let name = document.createElement("li")
                            let position = document.createElement("li")
                            let confidence = document.createElement("li")
                            let time = document.createElement("li")

                            id.innerHTML = DetectedItem.length
                            name.innerHTML = res.args.DetectedItem[i].label
                            position.innerHTML = res.args.DetectedItem[i].coordinate
                            confidence.innerHTML = res.args.DetectedItem[i].confidence
                            time.innerHTML = date.getFullYear() + "\\" + (date.getMonth() + 1) + "\\" + date.getDate() + "\\" + date.getHours() + "\\" + date.getMinutes() + "\\" + date.getSeconds()
                            ul.appendChild(id)
                            ul.appendChild(name)
                            ul.appendChild(position)
                            ul.appendChild(confidence)
                            ul.appendChild(time)
                            uls.prepend(ul)

                            // 获取坐标画矩阵    
                            ba_matrix.push(res.args.DetectedItem[i].coordinate)

                        }
                        uls.classList.add("add_info_main")
                        statusList[1].prepend(uls)



                        let div_cj = document.createElement("div")

                        div_cj.classList.add("add_info_main")

                        div_cj.style.marginTop = '20px'
                        div_cj.style.padding = '10px'



                        for (let m = 0; m < ba_matrix.length; m++) {     //框线矩阵  违禁物品
                            let [a, b, c, d] = [ba_matrix[m][0], ba_matrix[m][1], ba_matrix[m][2], ba_matrix[m][3]]
                            setTimeout(() => {
                                div_cj.appendChild(cropImage(`${img_url}/${res.args.OriginalImage}`, a, b, c, d))
                            }, 1000)
                        }
                        // 裁剪
                        right_top.appendChild(div_cj)

                    } else {
                        flages = 0
                        let ul = document.createElement('ul')
                        ul.style.display = "none"
                        statusList[1].prepend(ul)

                        let div = document.createElement("div")
                        div.style.display = 'none'
                        right_top.appendChild(div)
                    }
                    echarts_1()
                    echarts_2()
                    echarts_3()
                    
                    warn()
                    // 每有一张新的OriginalImage就创建一次 

                    let li = document.createElement('li')
                    li.style.border = '1px solid #add3ff'
                    // li.style.background = '#fff'    //修改  



                    //主图片
                    let img = document.createElement("img")
                    let img_url = getQueryAssetUrl()
                    img.src = `${img_url}/${res.args.OriginalImage}`
                    img.style.position = 'absolute'
                    li.appendChild(img)
                    //console.log(img_width + "   " + img_height)
                    //获取到的img也需要// position = 'absolute'    创建img

                    //let img_width =0   //原始图片的宽度
                    //let img_height = 0  //原始图片的高度
                    //let width_ratio = 0  //原始图片与控件的宽度比值
                    //let height_ratio = 0  //原始图片与控件的高度比值
                    var ratio = 0  //最终比例
                    img.onload = function () {
                        img_width = img.naturalWidth
                        img_height = img.naturalHeight
                        width_ratio = 1058 / img_width
                        height_ratio = 598 / img_height
                        //console.log(img_width + "   " + img_height)
                        for (let m = 0; m < ba_matrix.length; m++) {     //框线矩阵  违禁物品
                            let div = document.createElement("div")
                            div.style.position = 'absolute'
                            div.style.zIndex = '10'      //层级  
                            div.style.border = value + "px solid " + color
                            let [a, b, c, d] = [ba_matrix[m][0], ba_matrix[m][1], ba_matrix[m][2], ba_matrix[m][3]]
                            let [real_left, real_top, real_width, real_height] = [0, 0, 0, 0]
                            if (width_ratio > height_ratio)  //高度比值更小
                            {
                                var p_left = 0  //左坐标起始点
                                var p_top = 0  //上坐标起始点
                                ratio = height_ratio

                                p_left = (1058 - img_width * ratio) / 2
                                p_top = 0
                                real_left = p_left + a * ratio
                                real_top = p_top + b * ratio
                                real_width = c * ratio
                                real_height = d * ratio
                                div.style.left = real_left + 'px'
                                div.style.top = real_top + 'px'
                                div.style.width = real_width + 'px'
                                div.style.height = real_height + 'px'
                            }
                            else  //宽度比值更小
                            {
                                var p_left = 0  //左坐标起始点
                                var p_top = 0  //上坐标起始点
                                ratio = width_ratio

                                p_left = 0
                                p_top = (598 - img_height * ratio) / 2
                                real_left = p_left + a * ratio
                                real_top = p_top + b * ratio
                                real_width = c * ratio
                                real_height = d * ratio
                                div.style.left = real_left + 'px'
                                div.style.top = real_top + 'px'
                                div.style.width = real_width + 'px'
                                div.style.height = real_height + 'px'
                            }
                            li.appendChild(div)
                        }



                    }
                    box_center_ul.appendChild(li)



                    // updata   img
                    let up_li = li.cloneNode(true)
                    up_li.style.width = "200px"
                    up_li.style.height = "200px"
                    up_li.children[0].style.width = "200px"
                    up_li.children[0].style.height = "200px"
                    up_li.children[0].style.position = "static"

                    up_li.children[0].setAttribute("name", res.args.OriginalImage)
                    up_li.children[0].setAttribute("choice", "0")


                    // update_box_ul.appendChild(up_li)
                    box_update_le_ul.appendChild(up_li)


                    //update_box_ul.appendChild(up_li)



                    box_center_ul.style.width = box_center_ul.children.length + 1 + "00%"

                    banner()

                } else {
                    console.log("错误");
                }
            }
        }
    }
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "QueryResult");
    xhr.send()

}




// banner
let box_center_banner = document.querySelector(".box_center")
let box_center_ul = document.querySelector(".box_center_banner ul")
let jt_left = document.querySelector(".box_center_left")
let jt_right = document.querySelector(".box_center_right")
let max_img = document.querySelector(".max_img")
let box_center_span = document.querySelector(".max_img span")
let index = 0
let jl = true  //节流器
let bw = box_center_ul.children[0].clientWidth


// // banner
function banner() {


    //最大个数
    // 防止banner 数量过多

    if (box_center_ul.children.length >= 100) {

        //设置动画  
        setTimeout(() => {
            // ani.style.transition = '1s'
            ani.style.opacity = 1
            ani.style.display = 'block'
            setTimeout(() => {
                ani.style.opacity = 0
                ani.style.display = 'none'


            }, 1500)
        }, 150);
        // 去除一半
        for (let i = 0; i < parseInt(box_center_ul.children.length / 2); i++) {
            box_center_ul.removeChild(box_center_ul.children[i]);    //主界面图片
            right_top.removeChild(right_top.children[i]);   //记录图

        }
        index = box_center_ul.children.length - 2
        setTimeout(() => {
            box_center_ul.style.transition = "none"
            box_center_ul.style.left = index * -bw + 'px'

        }, 500)

    }



    function play() {

        // 清除详细信息样式
        if (!jl) return
        index++
        box_center_ul.style.transition = '1.5s'
        box_center_ul.style.left = index * -bw + 'px'

        remove_cla()
        statusList[1].children[box_center_ul.children.length - index - 1].classList.add("add_info_main")
        right_top.children[index - 1].classList.add("add_info_main")



        jl = false
        setTimeout(() => {
            jl = true
        }, 1500)

        // right_top.children[]
    }

    play()



    // statusList[1].children[index].style.boxShadow=' inset -3px -2px 5px 3px #add3ff, inset 3px 2px 5px 3px #add3ff;'
    // box_center_banner.onmousever
    box_center_banner.addEventListener("mouseenter", () => {
        clearInterval(timers)
        timers = null
        // mouseenter
    })
    box_center_banner.addEventListener('mouseleave', () => {
        clearInterval(timers)
        timers = setInterval(r_time, 3000)
        // mouseleave
    })

    jt_left.onclick = function () {
        if (!jl) return
        index--
        box_center_ul.style.transition = '1.5s'
        box_center_ul.style.left = index * -bw + 'px'

        // 清除详细信息样式
        remove_cla()
        statusList[1].children[box_center_ul.children.length - index - 1].classList.add("add_info_main")
        right_top.children[index - 1].classList.add("add_info_main")

        jl = false
        setTimeout(() => {
            jl = true
        }, 1500)
    }

    jt_right.onclick = play


    t = setInterval(() => {
        if (index >= box_center_ul.children.length - 1) {  //选择 -1  或不

            jt_right.style.display = 'none'

            //console.log("wul");

        } else {
            jt_right.style.display = 'block'

        }

        if (index > 1) {
            jt_left.style.display = 'block'
        } else if (index <= 1) {
            jt_left.style.display = 'none'
        }
    }, 100)




    // 且双击放大了变红色
    box_center_banner.ondblclick = function () {
        clearInterval(timers)
        timers = null
        max_img.children[0].src = box_center_ul.children[index].children[0].src
        max_img.style.display = 'block'
        vi_back.style.display = 'block'

    }
    box_center_span.onclick = function () {
        clearInterval(timers)
        timers = setInterval(r_time, 3000)
        max_img.style.display = 'none'
        max_img.children[0].src = ""

        vi_back.style.display = 'none'
    }



    // 图片滚轮局部放大缩小


    let all_li = box_center_ul.children

    let scale = 1; // 初始缩放比例
    let minScale = 1;
    let maxScale = 5;
    // 监听鼠标滚动事件
    // 监听鼠标滚动事件
    box_center_banner.addEventListener("wheel", function (e) {
        e.preventDefault();

        // 根据滚动方向调整缩放比例
        if (e.deltaY > 0) {
            scale -= 0.1; // 缩小
            scale = Math.max(scale, minScale); // 最小缩放比例限制
        } else {
            scale += 0.1; // 放大
            scale = Math.min(scale, maxScale); // 最大不超过5倍大小
        }
        for (var m = 0; m < all_li[index].children.length; m++) {
            // 获取鼠标在图片中的相对位置
            let mouseX = e.clientX - all_li[index].children[m].offsetLeft - 500;
            let mouseY = e.clientY - all_li[index].children[m].offsetTop;

            // 计算鼠标相对于图片的偏移比例
            let offsetX = mouseX / all_li[index].children[m].offsetWidth;
            let offsetY = mouseY / all_li[index].children[m].offsetHeight;

            // 设置图片的样式属性，实现局部放大效果
            all_li[index].children[m].style.transform = `scale(${scale})`;
            all_li[index].children[m].style.transformOrigin = `${offsetX * 100}% ${offsetY * 100}%`;
        }

    });

};








function ju_model(ModelName) {

    if (ModelName) {
        timers = setInterval(r_time, 3000)
        // clearInterval(timer)

    } else {
        console.log("选择模型后无返回的label");
    }
}

// crop image
function cropImage(ele, x, y, w, h) {
    // 创建一个新的 canvas 元素
    var canvas = document.createElement('canvas');
    var ctx = canvas.getContext('2d');


    // 设置 canvas 的尺寸与裁剪区域的尺寸一致
    canvas.width = w + 80; // 设置为裁剪的宽度
    canvas.height = h + 80; // 设置为裁剪的高度

    // 在 canvas 上绘制裁剪区域
    let box_img = document.createElement("img")

    box_img.src = ele;
    let can = document.createElement("img")
    box_img.onload = function () {
        // ctx.drawImage(box_img, x, y, w, h, 0, 0, w, h);
        //ctx.drawImage(box_img, x - w - 30, y + 50, w + 60, h + 60, 0, 0, w + 80, h + 80);
        ctx.drawImage(box_img, x, y, w, h, 0, 0, w + 80, h + 80);

        can.style.display = 'block'
        can.style.margin = 'auto'
        can.style.marginTop = '10px'

        // 将裁剪后的图片添加到 #croppedImage 的 src 属性中
        can.src = canvas.toDataURL('image/jpeg');
    }
    return can
}





// settings设置界面js

let confidence_sub = document.querySelector("#confidence")
let confidence_span = document.querySelector(".confidence_span")
let accuracy_sub = document.querySelector("#accuracy")
let accuracy_span = document.querySelector(".accuracy_span")


// change back
let back_color = document.querySelectorAll(".back_color div")
for (let j = 0; j < back_color.length; j++) {
    back_color[j].onclick = function () {

        background_color = back_color[j].style.background
        body.style.background = background_color
    }
}

// 粗细
let range = document.querySelector("#range")
let range_span = document.querySelector(".range_span")
let value = 1
range.addEventListener("input", function () {
    value = range.value / 10

    range_span.innerHTML = value
    ser.style.border = value + "px solid " + color
    bor_value = value
});


// 线框颜色
let linear_color_div = document.querySelectorAll(".linear_color div")
let ser = document.querySelector(".ser")
let color = linear_color_div[0].style.background
//    col()
for (let i = 0; i < linear_color_div.length; i++) {

    linear_color_div[i].onclick = function () {

        for (let z = 0; z < linear_color_div.length; z++) {
            linear_color_div[z].className = ''
        }
        linear_color_div[i].className = 'zt_on'
        ser.style.border = value + "px solid " + linear_color_div[i].style.background
        // 获取线框颜色传递index
        bor_color = linear_color_div[i].style.background
        // col()
        color = linear_color_div[i].style.background

    }
}

//   confidence

confidence.addEventListener("input", function () {
    const value = confidence.value;
    confidence_span.innerHTML = value


});


//   iou  accuracy
accuracy.addEventListener("input", function () {
    const value = accuracy.value;
    accuracy_span.innerHTML = value

});


// 提交设置
function settingsupdata() {

    var rgbValues = color.substring(4, color.length - 1).split(",");
    rgbValues = rgbValues.map(function (value) {
        return parseInt(value.trim());
    });


    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function () {
        if (xhr.status === 200 && xhr.readyState === 4) {
            // let res = JSON.parse(xhr.responseText)
            // console.log(xhr.responseText);

        }
    }
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "UpdateSettings");
    xhr.setRequestHeader("confidence", confidence_sub.value);
    xhr.setRequestHeader("iou", accuracy_sub.value);
    xhr.setRequestHeader("BoxColor", rgbValues);
    xhr.setRequestHeader("BoxLineSize", value);
    xhr.send()
};



// 统计界面
// (function () {

//     // time
//     let time_start = document.querySelector("#time_start")
//     let time_end = document.querySelector("#time_end")

//     time_start.onchange = function () {
//         console.log(time_start.value);
//     }
//     time_end.onchange = function () {
//         console.log(time_end.value);
//     }
// })();









function echarts_1() {
    sortedStatistics = Object.entries(update_echarts).sort((a, b) => b[1] - a[1]);
    titlename = []
    titlenum = []
    for (let n = 0; n < sortedStatistics.length; n++) {
        titlename[n] = sortedStatistics[n][0]
        titlenum[n] = sortedStatistics[n][1]
    }
    box_type_name = titlename
    while (titlename.length < 8) {
        box_type_name.push("1")
        titlenum.push(0)
    }
    

    // 基于准备好的dom，初始化echarts实例
    var myChart = echarts.init(document.getElementById('echart1'));



    option = {

        grid: {
            // width:"330px",
            left: '0%',
            top: '20px',
            right: '1px',
            bottom: '1px',
            containLabel: true
        },
        xAxis: [{
            name: "类别",
            type: 'category',
            data: titlename,
            // titlename





            axisLabel: {
                interval: 0,
                // rotate:50,
                show: true,
                splitNumber: 15,
                textStyle: {
                    color: "rgba(255,255,255,.9)",
                    fontSize: '12',
                },
            },
        }],
        yAxis: [{

            name: "数量",
            type: 'value',
            axisLabel: {
                //formatter: '{value} %'
                // show: true,
                textStyle: {
                    color: "rgba(255,255,255,.9)",
                    fontSize: '12',
                },
            },


            splitLine: {
                lineStyle: {
                    color: "rgba(255,255,255,.1)",
                }
            }
        }],
        series: [
            {

                type: 'bar',
                data: titlenum,
                // data:[123,543,756,333,23,65,8,8,76,777],

                barWidth: '35%', //柱子宽度
                // barGap: 1, //柱子之间间距
                itemStyle: {
                    normal: {
                        color: '#27d08a',
                        opacity: 1,
                        barBorderRadius: 5,

                    }
                },
                label: {
                    show: true,
                    position: 'top', // 设置标签显示在柱形顶部
                    textStyle: {
                        color: "#fff" // 设置标签文本颜色为白色
                    }
                }
            }

        ], dataZoom: [
            {
                type: "inside",  // 支持内部鼠标滚动平移
                start: 0,
                // end: 20,
                startValue: 0, // 从头开始。
                endValue: 5,  // 最多5个
                zoomOnMouseWheel: false,  // 关闭滚轮缩放
                moveOnMouseWheel: true, // 开启滚轮平移
                moveOnMouseMove: true  // 鼠标移动能触发数据窗口平移

            },
        ],

    };

    // 使用刚指定的配置项和数据显示图表。
    myChart.setOption(option);
    window.addEventListener("resize", function () {
        myChart.resize();
    });
};








function echarts_3() {
    sortedStatistics = Object.entries(update_echarts).sort((a, b) => b[1] - a[1]);
    titlename = []
    titlenum = []
    for (let n = 0; n < sortedStatistics.length; n++) {
        titlename[n] = sortedStatistics[n][0]
        titlenum[n] = sortedStatistics[n][1]
    }
    box_type_name = titlename
    while (titlename.length < 8) {
        box_type_name.push("1")
        titlenum.push(0)
    }

    data_pie = []
    for (let p = 0; p < titlename.length; p++) {
        data_pie[p] = { "name": titlename[p], "value": titlenum[p] }
    }

    // 基于准备好的dom，初始化echarts实例
    var myChart = echarts.init(document.getElementById('echart3'));
    option = {
        legend: {
            //orient: 'vertical',
            type: "scroll",
            selected: 10,

            top: '20',
            left: 'center',
            itemWidth: 10,
            itemHeight: 10,
            data: titlename,
            textStyle: {
                color: 'rgba(255,255,255,.5)',
                fontSize: '12',
            }
        },
        tooltip: {
            trigger: 'item',
            formatter: "{b} : {c} ({d}%)"
        },

        visualMap: {
            show: false,
            min: 500,
            max: 600,
            inRange: {
                //colorLightness: [0, 1]
            }
        },
        series: [{
            name: '分布',
            type: 'pie',
            radius: ['30%', '60%'],
            center: ['50%', '60%'],
            color: ['#0086e5', '#30c5ed', '#9fe7b8', '#fedb5b', '#ff9f7d', '#fb7293', '#e7bcf2'], //'#FBFE27','rgb(11,228,96)','#FE5050'
            data: data_pie,    //此处为数据 格式为 { "name": 类别, "value": 值 }
            roseType: 'radius',

            label: {
                normal: {
                    formatter: ['{d|{d}%}', '{b|{b}}'].join('\n'),
                    rich: {
                        d: {
                            color: 'rgb(241,246,104)',
                            fontSize: 14,
                            fontWeight: 'bold',

                        },
                        b: {
                            color: 'rgb(98,137,169)',
                            fontSize: 12,

                        },
                    },
                }
            },
            labelLine: {
                normal: {
                    lineStyle: {
                        color: 'rgb(98,137,169)',
                    },
                    smooth: 0.2,
                    length: 5,
                    length2: 9,

                }
            },
            itemStyle: {
                normal: {
                    shadowColor: 'rgba(0, 0, 0, 0.1)',
                    shadowBlur: 50,
                }
            }
        }]
    };
    // 使用刚指定的配置项和数据显示图表。
    myChart.setOption(option);

    window.addEventListener("resize", function () {
        myChart.resize();
    });
}






// update




let box_update_ce_li = document.querySelector(".box_update_ce li")  //点击传输

let box_update_ri_ul = document.querySelector(".box_update_ri ul")  //误测池

let jc_update = document.querySelector("#jc_update")

let bb_update = document.querySelector("#bb_update")


box_update_le_ul.onclick = function (e) {
    if (e.target.nodeName.toLowerCase() == 'img') {
        if (e.target.getAttribute("choice") == "0") {
            e.target.parentNode.style.boxShadow = "rgb(51 131 223) 2px 2px 2px 5px, rgb(51 131 223) -2px -2px 2px 5px";
            updata_name_src[e.target.name] = e.target.src
            e.target.setAttribute("choice", "1")

        } else if (e.target.getAttribute("choice") == "1") {
            e.target.setAttribute("choice", "0")
            e.target.parentNode.style.boxShadow = "none"
            delete updata_name_src[e.target.name];

        }


    }

}

box_update_ce_li.onclick = function () {
    //可能在此处提交

    for (let key in updata_name_src) {
        // name:key
        if (updata_name_src.hasOwnProperty(key)) {
            let li = document.createElement("li")
            let img = document.createElement("img")
            img.src = updata_name_src[key]
            li.appendChild(img)
            box_update_ri_ul.appendChild(li)
        }
    }
    updata_name_src = {}
}



let box_update_divs = document.querySelectorAll(".box_update_div")

// 加载条
let progress_load = document.querySelector(".progress_load")
let progress_load_result = document.querySelector(".progress_load_result")
let progress_load_timer = null
let progress_load_timer_i = 0




//放大  左池子

box_update_le_ul.ondblclick = function (e) {
    if (e.target.nodeName.toLowerCase() == 'img') {

        box_update_divs[0].style.display = 'block'
        box_update_divs[0].children[0].src = e.target.src

    }
}

box_update_divs[0].onclick = function (e) {
    if (e.target.nodeName.toLowerCase() == 'img') {
        e.target.parentNode.style.display = 'none'
    }

}

//右池子
box_update_ri_ul.ondblclick = function (e) {
    if (e.target.nodeName.toLowerCase() == 'img') {
        box_update_divs[1].style.display = 'block'
        box_update_divs[1].children[0].src = e.target.src

    }
}

box_update_divs[1].onclick = function (e) {
    if (e.target.nodeName.toLowerCase() == 'img') {
        e.target.parentNode.style.display = 'none'
    }
}



jc_update.onclick = function () {
    console.log("检测更新");

    // let xhr = new XMLHttpRequest()
    // xhr.onreadystatechange = function () {
    //     if (xhr.status === 200 && xhr.readyState === 4) {
    //         let res = JSON.parse(xhr.responseText)

    //     }
    // }
    // xhr.open("get", getQueryDataUrl())
    // xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    // xhr.setRequestHeader("cmd", "");
    // xhr.setRequestHeader("", updata_name);
    // xhr.send();
}

bb_update.onclick = function () {
    console.log("更新版本");

    progress_load_timer = setInterval(() => {
        if (progress_load_timer_i < 100) {
            progress_load_timer_i += 1;
            progress_load.style.width = progress_load_timer_i * 6 + 'px';
            progress_load_result.innerText = progress_load_timer_i + '%';
        }
        if (progress_load_timer_i >= 100) {
            clearInterval(progress_load_timer);
        }
    }, 100)



}




