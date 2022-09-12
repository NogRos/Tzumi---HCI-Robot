

// SEND GET MESSAGE
function upload_files() {
  const Http = new XMLHttpRequest();
  const url='http://192.168.137.1:8080';
  Http.open("GET", url);
  Http.send();
}

let flagForMessage = 0;
let initMessageFinished = 0;
let initCounter = 0;
const higherLevel = 25;
const lowerLevel = -25;

if (window.DeviceOrientationEvent) {
  window.addEventListener("deviceorientation", function(event) {
      // alpha: rotation around z-axis
      var rotateDegrees = event.alpha;
      // gamma: left to right
      var leftToRight = event.gamma;
      // beta: front back motion
      var frontToBack = event.beta;
      handleOrientationEvent(frontToBack, leftToRight, rotateDegrees);
  }, true);
}
else {
  document.body.style.backgroundColor = "red";
}


// CHECK ORIENTATION AND SEND MESSAGE WHEN OUT OF
var handleOrientationEvent = function(frontToBack, leftToRight, rotateDegrees) {
  //PREVENT INIT VALUES OF 0
  if (initCounter == 10) {
    //// FOR DEBUGGING
    //document.getElementById("x").innerHTML=frontToBack;
    //document.getElementById("y").innerHTML=leftToRight;

    //PHONE IS UP
    if ((frontToBack > higherLevel || frontToBack < lowerLevel || leftToRight > higherLevel || leftToRight < lowerLevel) && (initMessageFinished == 1) && (flagForMessage == 0)) {
      document.body.style.backgroundColor = "DarkSalmon";
      //document.getElementById("image").src='phoneUp.png';
      document.getElementById("TsumiT").innerHTML="Oh no!";
      document.getElementById("TsumiT2").innerHTML="Please put your phone down.. :(";
      upload_files();
      flagForMessage = 1;
    }
     //PHONE IS DOWN
    else if ((frontToBack < higherLevel && frontToBack > lowerLevel && leftToRight < higherLevel && leftToRight > lowerLevel) && initMessageFinished == 1){
      document.body.style.backgroundColor = "CornflowerBlue";
      //document.getElementById("image").src='TsumiHead.png';
      document.getElementById("TsumiT").innerHTML="";
      document.getElementById("TsumiT2").innerHTML="";
      flagForMessage = 0;
    }
    //PHONE IS DOWN FOR THE FIRST TIME
    else if ((initMessageFinished == 0) && (frontToBack < higherLevel) && (frontToBack > lowerLevel) && (leftToRight < higherLevel) && (leftToRight > lowerLevel)) {
      document.getElementById("image").src='TsumiHead.png';
      initMessageFinished = 1;
      document.getElementById("TsumiT").innerHTML="";
      document.getElementById("TsumiT2").innerHTML="";
      document.getElementById("message").innerHTML="";
      document.body.style.backgroundColor = "CornflowerBlue";
    }

  }
  else {
    initCounter += 1;
    //// FOR DEBUGGING
    //document.getElementById("z").innerHTML=initCounter;
  }


};

