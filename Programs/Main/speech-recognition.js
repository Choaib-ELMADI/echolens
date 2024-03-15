document.onreadystatechange = function () {
	if (document.readyState == "complete") {
		const listeningCheckbox = document.getElementById("toggle-listening");
		const listeningIndicator = document.getElementById("listening-indicator");

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
