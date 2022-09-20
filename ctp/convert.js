'use strict';

const fs = require('fs');

let rawdata = fs.readFileSync('brokers.json');
let brokers = JSON.parse(rawdata);

let output = [];
brokers.forEach(function(x){
	let a,b,c,d,e,f,g;

	[a,b,c,d,e,f,g] = x;
	let broker = { 
		"brokerName": a,
		"brokerId": d,
		"marketServer": f,
		"tradeServer": g
	};
	output.push(broker);
});

let str = JSON.stringify(output, null, 2);
console.log(str);

