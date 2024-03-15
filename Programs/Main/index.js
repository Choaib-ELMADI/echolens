/*
document.onreadystatechange = function () {
	if (document.readyState == "complete") {
		// let baseHost = document.location.origin;
		// let streamUrl = baseHost + ":81/stream";
		// var xmlHttp = createXMLHttpObject();

		//! IMAGE GROUP (1)
		// const imageCheckbox = document.getElementById("show-hide-image");
		// const viewStream = document.getElementById("stream-image");
		// viewStream.src = streamUrl;
		// const viewStreamContainer = document.getElementById("stream-container");
		// const ledIntensitySlider = document.getElementById("led-intensity-slider");

		//! TALKING GROUP (1)
		// const talkingCheckbox = document.getElementById("toggle-talking");
		// const talkingIndicator = document.getElementById("talking-indicator");

		//! DARK/LIGHT MODE (1)
		// const toggleDarkLightMode = document.getElementById("dark-light-mode");
		// const currentMode = document.getElementById("dark-light-curr-mode");

		// * =========================================================================================

		//! IMAGE GROUP (2)
		// handleCheckboxChange(imageCheckbox, viewStreamContainer);
		// imageCheckbox.addEventListener("change", () => {
		// 	listeningCheckbox.checked = false;
		// 	talkingCheckbox.checked = false;

		// 	handleCheckboxChange(listeningCheckbox, listeningIndicator);
		// 	handleCheckboxChange(talkingCheckbox, talkingIndicator);
		// 	handleCheckboxChange(imageCheckbox, viewStreamContainer);

		// 	handleToggleViewStream();
		// });
		// handleSliderIntensityUpdate();
		// ledIntensitySlider.oninput = handleSliderIntensityUpdate;

		//! TALKING GROUP (2)
		// handleCheckboxChange(talkingCheckbox, talkingIndicator);
		// talkingCheckbox.addEventListener("change", () => {
		// 	imageCheckbox.checked = false;
		// 	listeningCheckbox.checked = false;

		// 	handleCheckboxChange(imageCheckbox, viewStreamContainer);
		// 	handleCheckboxChange(listeningCheckbox, listeningIndicator);
		// 	handleCheckboxChange(talkingCheckbox, talkingIndicator);

		// 	handleToggleTalking();
		// });

		// process();

		// * FUNCTIONS HERE

		// function createXMLHttpObject() {
		// 	if (window.XMLHttpRequest) {
		// 		xmlHttp = new XMLHttpRequest();
		// 	} else {
		// 		xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
		// 	}
		// 	return xmlHttp;
		// }

		// function handleToggleViewStream() {
		// 	let xhttp = new XMLHttpRequest();
		// 	xhttp.open("PUT", "TOGGLE_VIEW_STREAM", false);
		// 	xhttp.send();
		// }
		// function handleToggleListening() {
		// 	let xhttp = new XMLHttpRequest();
		// 	xhttp.open("PUT", "TOGGLE_LISTENING", false);
		// 	xhttp.send();
		// }
		// function handleToggleTalking() {
		// 	let xhttp = new XMLHttpRequest();
		// 	xhttp.open("PUT", "TOGGLE_TALKING", false);
		// 	xhttp.send();
		// }
		// function handleSliderIntensityUpdate() {
		// 	let xhttp = new XMLHttpRequest();
		// 	xhttp.open("PUT", "UPDATE_INTENSITY?intensity=" + this.value, false);
		// 	xhttp.send();
		// }

		// function updateDateTime() {
		// 	const dateContainer = document.getElementById("date-container");
		// 	const timeContainer = document.getElementById("time-container");
		// 	const dt = new Date();

		// 	dateContainer.innerHTML = `<small>Date:</small> ${dt.toLocaleDateString()}`;
		// 	timeContainer.innerHTML = `<small>Time:</small> ${dt.toLocaleTimeString(
		// 		"en-US",
		// 		{ hour12: false }
		// 	)}`;
		// }

		function hide(el) {
			el.style.display = "none";
		}
		function show(el) {
			el.style.display = "flex";
		}

		function handleCheckboxChange(checkboxEl, el) {
			if (checkboxEl.checked) {
				show(el);
			} else {
				hide(el);
			}
		}

		// function response() {
		// 	let xmlResponse;
		// 	let xmlDoc;
		// 	let message;

		// 	xmlResponse = xmlHttp.responseXML;
		// 	console.log(xmlResponse);

		// 	/* xmlDoc = xmlResponse.getElementsByTagName("StreamState");
		// 				message = xmlDoc[0].firstChild.nodeValue;
		// 				if (message == 0) imageCheckbox.checked = false;
		// 				else imageCheckbox.checked = true;

		// 				xmlDoc = xmlResponse.getElementsByTagName("ListeningState");
		// 				message = xmlDoc[0].firstChild.nodeValue;
		// 				if (message == 0) listeningCheckbox.checked = false;
		// 				else listeningCheckbox.checked = true;

		// 				xmlDoc = xmlResponse.getElementsByTagName("TalkingState");
		// 				message = xmlDoc[0].firstChild.nodeValue;
		// 				if (message == 0) talkingCheckbox.checked = false;
		// 				else talkingCheckbox.checked = true;
		// }

		// function process() {
		// 	updateDateTime();

		// 	if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
		// 		xmlHttp.open("PUT", "xml", true);
		// 		xmlHttp.onreadystatechange = response;
		// 		xmlHttp.send(null);
		// 	}

		// 	setTimeout(process, 40);
// }
	}
}
*/

document.onreadystatechange = function () {
	if (document.readyState == "complete") {
		//* ==== Request Group ==== *//
		// let baseHost = document.location.origin;
		// let streamUrl = baseHost + ":81/stream";
		// var xmlHttp = createXMLHttpObject();

		//* ==== Image Group ==== *//
		// const imageCheckbox = document.getElementById("show-hide-image");
		// const viewStream = document.getElementById("stream-image");
		// viewStream.src = streamUrl;
		// const viewStreamContainer = document.getElementById("stream-container");
		// const ledIntensitySlider = document.getElementById("led-intensity-slider");

		//* ==== Dark/Light Mode Group ==== *//
		const toggleDarkLightMode = document.getElementById("dark-light-mode");
		const currentMode = document.getElementById("dark-light-curr-mode");

		//* ==== Listen Group ==== *//
		const listeningCheckbox = document.getElementById("toggle-listening");
		const listeningIndicator = document.getElementById("listening-indicator");

		//* ==== Talk Group ==== *//
		// const talkingCheckbox = document.getElementById("toggle-talking");
		// const talkingIndicator = document.getElementById("talking-indicator");

		//* ==== Speech Group ==== *//
		const speechContainer = document.getElementById("speech-container");
		const generatedTextContainer = document.getElementById(
			"generated-text-container"
		);
		const clearGeneratedTextBtn = document.getElementById(
			"clear-generated-text"
		);
		let generatedText = "";
		let recognition = null;

		//* ========================================================================================= *//

		//* ==== Dark/Light Mode Group ==== *//
		toggleDarkLightMode.addEventListener("change", () => {
			document.body.classList.toggle("light");

			if (document.body.classList.contains("light")) {
				currentMode.innerText = "Light";
			} else {
				currentMode.innerText = "Dark";
			}
		});

		//* ==== Speech Group ==== *//
		setUpSpeech("en-US");
		handleShowText(generatedText);
		handleCheckboxChange(listeningCheckbox, listeningIndicator);
		listeningCheckbox.addEventListener("change", () => {
			handleCheckboxChange(listeningCheckbox, listeningIndicator);

			if (listeningCheckbox.checked) {
				generatedText = "";
				handleShowText(generatedText);
				console.log("Checked");
				recognition.start();
			} else {
				console.log("Unchecked");
				recognition.stop();
			}
		});
		clearGeneratedTextBtn.addEventListener("click", () => {
			console.log("Text cleared");
			generatedText = "";
			handleShowText(generatedText);
		});

		//* ========================================================================================= *//

		function setUpSpeech(lang) {
			recognition = new webkitSpeechRecognition();
			recognition.continuous = true;
			recognition.interimResults = true;
			recognition.lang = lang;

			return new Promise((resolve, reject) => {
				recognition.onresult = function (event) {
					let interimTranscript = "";
					let finalTranscript = "";

					for (let i = event.resultIndex; i < event.results.length; ++i) {
						const transcript = event.results[i][0].transcript;

						if (event.results[i].isFinal) {
							finalTranscript += transcript;
						} else {
							interimTranscript += transcript;
						}
					}

					generatedText = finalTranscript;
					handleShowText(generatedText);
				};

				recognition.onerror = function (event) {
					console.error("Speech recognition error: ", event.error);
					listeningCheckbox.checked = false;
					handleCheckboxChange(listeningCheckbox, listeningIndicator);
					reject(event.error);
				};

				recognition.onend = function () {
					console.log("Speech recognition ended");
					listeningCheckbox.checked = false;
					handleCheckboxChange(listeningCheckbox, listeningIndicator);
				};

				resolve();
			});
		}

		function handleShowText(generatedText) {
			if (generatedText) {
				generatedTextContainer.innerText = generatedText;
				speechContainer.style.display = "flex";
			} else {
				speechContainer.style.display = "none";
			}
		}

		function hide(el) {
			el.style.display = "none";
		}
		function show(el) {
			el.style.display = "flex";
		}

		function handleCheckboxChange(checkboxEl, el) {
			if (checkboxEl.checked) {
				show(el);
			} else {
				hide(el);
			}
		}
	}
};
