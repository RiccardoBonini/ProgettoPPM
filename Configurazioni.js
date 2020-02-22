const MySocket = new WebSocket('ws://192.168.43.209:256');//alternative socket 'ws://172.18.82.53:255'


function connect(){
    this.MySocket = new WebSocket('ws://192.168.43.209:256')
}

function driveMode() {
    //const socket = new WebSocket('ws://192.168.43.201:255', ["protocolOne", "protocolTwo"]);
    var msg = {
        dir1: "avanti",
        dir2: "indietro",
        dir3: "ruotaDestra",
        dir4: "ruotaSinistra"
    };
    if(MySocket.readyState == 1) {
        MySocket.send(JSON.stringify(msg));
    }

}

function cookingMode(){
    var msg = {
        dir1: "avanti",
        dir2: "indietro",
        dir3: "destra",
        dir4: "sinistra"
    };
    if(MySocket.readyState == 1) {
        MySocket.send(JSON.stringify(msg));
    }

}

function reverseDriveMode(){
    var msg = {
        dir1: "indietro",
        dir2: "avanti",
        dir3: "ruotaSinistra",
        dir4: "ruotaDestra"
    };
    if(MySocket.readyState == 1) {
        MySocket.send(JSON.stringify(msg));
    }

}