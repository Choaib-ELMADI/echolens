document.onreadystatechange = function () {
	if (document.readyState == "complete") {
		//===>
		const languageForm = document.getElementById("language-form");
		let selectedLanguage = "EN";
		const speechLanguages = { EN: "en-US", FR: "fr-FR", AR: "ar-SA" };

		//===>
		const listeningCheckbox = document.getElementById("toggle-listening");
		const listeningIndicator = document.getElementById("listening-indicator");

		//===>
		const talkingCheckbox = document.getElementById("toggle-talking");
		const talkingIndicator = document.getElementById("talking-indicator");

		//===>
		const speechContainer = document.getElementById("speech-container");
		const generatedTextContainer = document.getElementById("generated-text");
		const clearGeneratedTextBtn = document.getElementById(
			"clear-generated-text"
		);
		let generatedText = "";
		let recognition = null;

		//===>
		const signsContainer = document.getElementById("signs-container");
		const signTextContainer = document.getElementById("sign-text");
		const clearSignTextBtn = document.getElementById("clear-sign-text");
		const playSignTextBtn = document.getElementById("play-sign-text");
		let signText = "";

		//===>
		const toggleDarkLightMode = document.getElementById("dark-light-mode");
		const currentMode = document.getElementById("dark-light-curr-mode");

		//* ========================================================================================= *//

		//===>
		handleSelectedLanguage();
		languageForm.addEventListener("change", handleSelectedLanguage);

		//===>
		setUpSpeech(speechLanguages[selectedLanguage]);
		handleShowText(generatedText);
		handleToggleListening(0);
		handleCheckboxChange(listeningCheckbox, listeningIndicator);
		listeningCheckbox.addEventListener("change", () => {
			handleCheckboxChange(listeningCheckbox, listeningIndicator);

			talkingCheckbox.checked = false;
			handleCheckboxChange(talkingCheckbox, talkingIndicator);

			if (listeningCheckbox.checked) {
				console.log("Stoped Talking.");
				handleToggleTalking(0);

				generatedText = "";
				handleShowText(generatedText);
				console.log("Listening...");
				handleToggleListening(1);
				recognition.start();
			} else {
				console.log("Stoped Listening.");
				handleToggleListening(0);
				recognition.stop();
			}
		});

		//===>
		handleToggleTalking(0);
		handleCheckboxChange(talkingCheckbox, talkingIndicator);
		talkingCheckbox.addEventListener("change", () => {
			handleCheckboxChange(talkingCheckbox, talkingIndicator);

			listeningCheckbox.checked = false;
			handleCheckboxChange(listeningCheckbox, listeningIndicator);

			if (talkingCheckbox.checked) {
				console.log("Stoped Listening.");
				handleToggleListening(0);
				recognition.stop();

				console.log("Talking...");
				handleToggleTalking(1);
			} else {
				console.log("Stoped Talking.");
				handleToggleTalking(0);
			}
		});

		//===>
		clearGeneratedTextBtn.addEventListener("click", () => {
			console.log("Text cleared");
			generatedText = "";
			handleShowText(generatedText);
		});

		//===>
		handleShowSignText(signText);
		clearSignTextBtn.addEventListener("click", () => {
			console.log("Text cleared");
			signText = "";
			handleShowSignText(signText);
		});
		playSignTextBtn.addEventListener("click", () => {
			playSignText();
		});

		//===>
		toggleDarkLightMode.addEventListener("change", () => {
			document.body.classList.toggle("light");

			if (document.body.classList.contains("light")) {
				currentMode.innerText = "Light";
			} else {
				currentMode.innerText = "Dark";
			}
		});

		//===>
		process();

		//* ========================================================================================= *//
		function handleSelectedLanguage() {
			let xhttp = new XMLHttpRequest();
			const selectedLanguageInput = document.querySelector(
				'input[name="language"]:checked'
			);

			selectedLanguage = selectedLanguageInput.value;
			xhttp.open("PUT", "GET_SELECTED_LANG?lang=" + selectedLanguage, false);
			xhttp.send();
		}

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
					handleToggleListening(0);
					reject(event.error);
				};

				recognition.onend = function () {
					console.log("Speech recognition ended.");
					listeningCheckbox.checked = false;
					handleToggleListening(0);
					handleCheckboxChange(listeningCheckbox, listeningIndicator);
				};

				resolve();
			});
		}

		function playSignText() {
			console.log(`Playing ${signText}`);
		}

		function handleShowText(generatedText) {
			if (generatedText) {
				generatedTextContainer.innerText = generatedText;
				speechContainer.style.display = "flex";
			} else {
				speechContainer.style.display = "none";
			}
		}
		function handleShowSignText(signText) {
			if (signText && signText !== "_BLANK_") {
				signTextContainer.innerText = signText;
				signsContainer.style.display = "flex";
			} else {
				signsContainer.style.display = "none";
			}
		}

		function handleToggleListening(listeningState) {
			let xhttp = new XMLHttpRequest();
			xhttp.open("PUT", "TOGGLE_LISTENING?state=" + listeningState, false);
			xhttp.send();
		}
		function handleToggleTalking(talkingState) {
			let xhttp = new XMLHttpRequest();
			xhttp.open("PUT", "TOGGLE_TALKING?state=" + talkingState, false);
			xhttp.send();
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

		function updateDateTime() {
			const dateContainer = document.getElementById("date-container");
			const timeContainer = document.getElementById("time-container");
			const dt = new Date();

			dateContainer.innerHTML = `<small>Date:</small> ${dt.toLocaleDateString()}`;
			timeContainer.innerHTML = `<small>Time:</small> ${dt.toLocaleTimeString(
				"en-US",
				{ hour12: false }
			)}`;
		}
		function response() {
			if (talkingCheckbox.checked) {
				fetch("http://192.168.169.196/SEND_TEXT_SIGN")
					.then((resu) => resu.text())
					.then((data) => {
						signText = data;
						handleShowSignText(signText);
					});
			}
		}
		function process() {
			updateDateTime();
			response();
			setTimeout(process, 40);
		}
	}
};
