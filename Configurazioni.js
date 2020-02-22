const MySocket = new WebSocket('ws://192.168.43.209:256');//alternative socket 'ws://172.18.82.53:255'


function connect(){
    this.MySocket = new WebSocket('ws://192.168.43.209:256')
}

function send1() {
    //const socket = new WebSocket('ws://192.168.43.201:255', ["protocolOne", "protocolTwo"]);
    var msg = {
        type: "message",
        text: "aooo",
    };
    if(MySocket.readyState == 1) {
        MySocket.send(JSON.stringify(msg));

    }

}

function send2(){}

function send3(){}