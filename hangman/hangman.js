var wrongX = 10, correctX = 670;
var wrongJ = 30, correctJ = 30;
var i = 0; j = 0;
var count = 0, rounds = 0;
var isRunning = false;
var guessed = [];
var state = [];
var myWords = ["WRISTWATCH", "YOU CAN CATCH MORE FLIES WITH HONEY THAN YOU CAN WITH VINEGAR", "HAVE YOU EVER HAD SEX WITH A PHARAOH AH PUT THE PUSSY IN A SARCOPHAGUS","ONCE UPON A TIME IN A GALAXY FAR FAR AWAY","REST IN PEACE TO AALIYAH REST IN PEACE TO LEFT EYE MICHAEL JACKSON I SEE JUST AS SOON AS I DIE", "WHO IS SAMUEL CLEMENS", "YOU CANT UNSCRAMBLE EGGS", "Phomas"];
var answerKey = "";
var guessPhrase = false;
var winLose = "";

function drawTree() {
	isRunning = true;
	drawTree2(500, 20, 500, 50);
	
	drawTree2(500, 20, 650, 20);
	
	drawTree2(650, 20, 650, 220);
	
	drawTree2(570, 220, 730, 220);
	
	var num = Math.floor((Math.random() * 7));
	answerKey = myWords[num];
	createText();
	gameState();
	document.write(Date());
}

function drawTree2(startX, startY, endX, endY) {
	var context = document.getElementById("grid").getContext("2d");
	context.beginPath();
	context.moveTo(startX, startY);
	context.lineTo(endX, endY);
	context.stroke();
}

function userGuess() {
	rounds = rounds + 1;
	var context = document.getElementById("grid").getContext("2d");
	var myText = document.forms["userGuess"]["guess"].value;
	context.font = "14px Georgia";
	var tempText = myText.toUpperCase();
	if( count >= 6 || tempText.length > 1 || isRunning == false) {
		//do nothing
	}
	else if( (answerKey.includes(tempText) == false && guessed.includes(tempText) == false)) {
			printGuess(tempText, false);
			i = i + 15;
			if(count < 6) {
				updateTree();
			}
	}
	else {
		i = i + 15;
		guessed.push(tempText);
		updateGuess(tempText);
	}
	if(i >= 263) {
		i = 10;
		j = j + 10;
	}
}


function updateTree() {
	var context = document.getElementById("grid").getContext("2d");
	if(count == 0) {
		context.beginPath();
		context.arc(500, 75, 25, 0, 2*Math.PI);
		context.stroke();
		count = count + 1;
	}
	else {
		if(count == 1) {
			drawTree2(500, 100, 500, 150);
			count = count + 1;
		}else if(count > 1 && count < 4) {
			if(count % 2 == 0) {
				drawTree2(500, 110, 475, 135);
				count = count + 1;
			}else {
				drawTree2(500, 110, 525, 135);
				count = count + 1;
			}
		}else{
			if(count % 2 == 0) {
				drawTree2(500, 150, 475, 175);
				count = count + 1;
			}else {
				winLose = "loss";
				drawTree2(500, 150, 525, 175);
				count = count + 1;
				isRunning = false;
				var until = 0;
				for(until = 0; until < answerKey.length; until++) {
					if(answerKey.charAt(until) != " ") {
						updateGuess(answerKey.charAt(until));
					}
				}
				printMessage();
			}
		}	
	}
}



function createText() {
	var i, posX = 50, posY = 300, j = 0;
	var context = document.getElementById("grid").getContext("2d");
	context.font = "14px Georgia";
	var wordArray = answerKey.split(" ");
	for(i = 0; i < wordArray.length; i++) {
		var tempWord = wordArray[i];
		var overflow = tempWord.length * 13 + posX;
		for(j = 0; j < tempWord.length; j++) {
			if(overflow >= 850) {
				posX = 50;
				posY = posY + 35;
				overflow = tempWord.length * 13 + posX;
			}
				context.fillText("_", posX, posY);
				posX = posX + 13;
		}
		posX = posX + 13;
	}
	
	context.fillText("Incorrect guesses", 10, 10);
	context.fillText("Correct guesses", 673, 10);
}


function updateGuess(guess) {
	var posX = 50, posY = 300, i = 0, j = 0;
	var context = document.getElementById("grid").getContext("2d");
	context.font = "14px Georgia";
	var wordArray = answerKey.split(" ");
	for(i = 0; i < wordArray.length; i++) {
		var tempWord = wordArray[i];
		var overflow = tempWord.length * 13 + posX;
		for(j = 0; j < tempWord.length; j++) { 
			if(overflow >= 850){
				posX = 50;
				posY = posY + 35;
				overflow = tempWord.length * 13 + posX;
			}
			if(tempWord.charAt(j) == guess) {
				context.fillText(guess, posX, posY);
				posX = posX + 13;
			}else {
				posX = posX + 13;
			}
		}
		posX = posX + 13;
	}
	gameState();
	printGuess(guess, true);
}

function userGuessPhrase() {
	var context = document.getElementById("grid").getContext("2d");
	var myText = document.forms["userGuess"]["guess"].value;
	var guess = myText.toUpperCase();
	if(guess == answerKey) {
		winLose = "win";
		var loopV = 0;
		for(loopV = 0; loopV < guess.length; loopV++) {
			if(guess.charAt(loopV) != " ") {
				updateGuess(guess.charAt(loopV));
			}
		}
		isRunning = false;
		printMessage();
	}else {
		winLose = "loss";
		var until = 0;
		for(until = count; until < 6; until++) {
			updateTree();
		}
		for(until = 0; until < answerKey.length; until++) {
			if(answerKey.charAt(until) != " ") {
				updateGuess(answerKey.charAt(until));
			}
		}
		printMessage();
	}
	guessPhrase = true;
}

function gameState() {
	if(rounds == 0) {
		var c = 0;
		for(c = 0; c < answerKey.length; c++) {
			if(!state.includes(answerKey.charAt(c))) {
				state.push(answerKey.charAt(c));
			}
		}
	}else {
		var c = 0;
		for(c = 0; c < guessed.length; c++) {
			if(state.includes(guessed[c])) {
				state.splice(state.indexOf(guessed[c]), state.indexOf(guessed[c])+1);
			}
		}
	}
	if(state.length == 0 && rounds != 0) {
		isRunning = false;
		winLose = "win";
		printMessage();
	}
}

function printMessage() {
	var context = document.getElementById("grid").getContext("2d");
	context.font = "14px Georgia";
	if(winLose == "win") {
		var message = "Congrats You Win!!";
		context.fillText(message, 670, 30);
	}else {
		var message = "Sorry You Lose :(";
		context.fillText(message, 670, 30);
	}		
}

function printGuess(letter, isCorrect) {
	var context = document.getElementById("grid").getContext("2d");
	context.font = "14px Georgia";
	if(isCorrect) {
		context.fillText(letter, correctX, correctJ);
		correctX = correctX +14;
	}else {
		context.fillText(letter, wrongX, wrongJ);
		wrongX = wrongX + 14;
	}
	
	if(wrongX >= 263) {
		wrongX = 10;
		wrongJ = wrongJ + 13;
	}
	
	if(correctX >= 963) {
		correctX = 670;
		correctJ = correctJ + 13;
	}
}
