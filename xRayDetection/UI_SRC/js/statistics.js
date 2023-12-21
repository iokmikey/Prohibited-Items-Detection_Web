

var label = []
var statistics = []
let body = document.querySelector("body")
window.onload = function () {
    var urlParams = new URLSearchParams(window.location.search);
    var selectedParam = urlParams.get('selected');  //获取发送过来的模型名字
    var background_color = urlParams.get("back")  //背景
    body.style.background = background_color

    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function () {
        if (xhr.status === 200 && xhr.readyState === 4) {
            let res = JSON.parse(xhr.responseText)

            label = res.args.label
            statistics = res.args.statistics

        }


    }
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "SwitchModel");
    xhr.setRequestHeader("ModelName", selectedParam);
    xhr.send()


};

(function () {

    // time
    let time_start = document.querySelector("#time_start")
    let time_end = document.querySelector("#time_end")

    time_start.onchange = function () {
        console.log(time_start.value);
    }
    time_end.onchange = function () {
        console.log(time_end.value);
    }




})();


// var data_type = []  //左边全部数据
// for (let i = 0; i < 14; i++) {
//     data_type[i] = String(i)
// }
// var data = [ 345, 320, 280, 271, 254, 229, 210, 190, 271, 254, 229, 210, 190, 1000]


//  // 模拟json排序
//  var jsons = { "data": [] }
//  for (let j = 0; j < data.length; j++) {
//      jsons.data[j] = { "name": data_type[j], "value": data[j] }
//  }

//  function down(x, y) {
//      return y.value - x.value
//  }
//  jsons.data.sort(down)



//  var titlename = []
//  var titlenum = []
//  for (let n = 0; n < data.length; n++) {
//      titlename[n] = jsons.data[n].name
//      titlenum[n] = jsons.data[n].value
//  }


//    进行排序分割 
let sortedStatistics = Object.entries(statistics).sort((a, b) => b[1] - a[1]);
var titlename = []
var titlenum = []
for (let n = 0; n < sortedStatistics.length; n++) {
    titlename[n] = sortedStatistics[n][0]
    titlenum[n] = sortedStatistics[n][1]
}


echarts_1()
function echarts_1() {





    // 基于准备好的dom，初始化echarts实例
    var myChart = echarts.init(document.getElementById('echart1'));

    option = {

        grid: {
            left: '0%',
            top: '20px',
            right: '0%',
            bottom: '0',
            containLabel: true
        },
        xAxis: [{
            name: "类别",
            type: 'category',
            data: titlename,



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

        ]
    };

    // 使用刚指定的配置项和数据显示图表。
    myChart.setOption(option);
    window.addEventListener("resize", function () {
        myChart.resize();
    });
};



// 制作数据
let data_pie = []
for (let p = 0; p < titlename.length; p++) {
    data[p] = { "name": titlename[p], "value": titlenum[p] }
}



echarts_2()
function echarts_2() {
    // 基于准备好的dom，初始化echarts实例
    var myChart = echarts.init(document.getElementById('echart2'));
    option = {
        legend: {
            //orient: 'vertical',
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
