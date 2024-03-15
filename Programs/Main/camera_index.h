#include "Arduino.h"

const char htmlWebPage[] PROGMEM = R"RAW(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8" />
            <meta name="viewport" content="width=device-width,initial-scale=1" />
            <title>EchoLens | Smart Device</title>
            <style>
                * {
                    padding: 0;
                    margin: 0;
                    box-sizing: border-box;

                    &::-webkit-scrollbar {
                        width: 10px;
                        padding: 1px;
                        background: var(--back);

                        display: none;
                    }
                    &::-webkit-scrollbar-thumb {
                        width: 8px;
                        border-radius: 8px;
                        background: var(--second__back);
                    }
                }

                body {
                    --large: 16px;
                    --medium: 14px;
                    --small: 13px;

                    --spacing: 20px;

                    --back: #181818;
                    --text: #efefef;
                    --second__back: #272727;
                    --second__text: #717171;
                    --green: #2aa451;
                    --red: #e6618c;
                    --purple: #6d5fb4;

                    font-family: Arial, Helvetica, sans-serif;
                    background: var(--back);
                    color: var(--text);
                    font-size: var(--large);

                    @media screen and (width <= 800px) {
                        --spacing: 10px;

                        font-size: var(--medium);
                    }

                    &.light {
                        --back: #9d9999;
                        --text: #181818;
                        --second__back: #c3bdbd;
                        --second__text: #272727;
                    }

                    .main {
                        width: calc(100% - calc(var(--spacing) * 2));
                        max-width: 1600px;
                        margin-inline: auto;

                        min-height: calc(100vh - calc(var(--spacing) * 2));
                        margin-block: var(--spacing);

                        background: var(--second__back);
                        border-radius: var(--spacing);
                        padding: var(--spacing);

                        display: flex;
                        flex-direction: column;
                        gap: 0.5rem;

                        @media screen and (width <= 800px) {
                            padding: calc(var(--spacing) * 1.5);
                        }

                        @media screen and (width <= 368px) {
                            padding: var(--spacing);
                        }

                        .page-header {
                            display: flex;
                            flex-direction: column;
                            gap: 3rem;

                            .page-header__top {
                                display: flex;
                                align-items: start;
                                justify-content: space-between;
                                gap: 0.25rem;

                                .slogan {
                                    text-align: left;
                                    background: linear-gradient(
                                        to bottom right,
                                        var(--second__text),
                                        var(--text),
                                        var(--second__text)
                                    );
                                    background-clip: text;
                                    color: transparent;
                                }

                                .toggle-container {
                                    color: var(--second__text);
                                    font-weight: 700;
                                    font-size: 1.5rem;
                                    display: flex;
                                    user-select: none;

                                    .toggle {
                                        width: 22px;
                                        height: 3rem;
                                        background: var(--red);
                                        border-radius: 11px;
                                        padding: 2px;
                                        cursor: pointer;
                                        display: flex;
                                        justify-content: center;
                                        transition: background 300ms 300ms;

                                        .toggle__circle {
                                            width: 18px;
                                            height: 18px;
                                            background: var(--text);
                                            border-radius: 50%;
                                            margin-top: calc(3rem - 22px);
                                            transition: margin 500ms ease-in-out;
                                        }
                                    }

                                    .toggle-text {
                                        display: flex;
                                        flex-direction: column;
                                        line-height: 1.5rem;
                                        margin-left: 1px;

                                        background: linear-gradient(
                                            to bottom,
                                            var(--text),
                                            var(--second__text),
                                            var(--text)
                                        );
                                        background-clip: text;
                                        color: transparent;
                                    }

                                    #show-hide-image:checked + .toggle {
                                        background: var(--green);

                                        & > .toggle__circle {
                                            margin-top: 0.5px;
                                        }
                                    }
                                }
                            }

                            .page-header__bottom {
                                font-size: var(--large);

                                display: flex;
                                align-items: center;
                                gap: 0.5rem;

                                @media screen and (width <= 460px) {
                                    flex-direction: column;
                                    align-items: start;
                                }

                                .mode-toggle-container {
                                    margin-right: auto;
                                    display: flex;
                                    align-items: center;
                                    gap: 0.5rem;

                                    .toggle {
                                        width: 3rem;
                                        height: 22px;
                                        background: var(--red);
                                        border-radius: 11px;
                                        padding: 2px;
                                        cursor: pointer;
                                        display: flex;
                                        justify-content: start;
                                        transition: background 300ms 300ms;

                                        .toggle__circle {
                                            width: 18px;
                                            height: 18px;
                                            background: var(--text);
                                            border-radius: 50%;
                                            margin-left: 0.5px;
                                            transition: margin 500ms ease-in-out;
                                        }
                                    }

                                    #dark-light-mode:checked + .toggle {
                                        background: var(--green);

                                        & > .toggle__circle {
                                            margin-left: calc(3rem - 22px);
                                        }
                                    }

                                    p {
                                        font-weight: bold;
                                        background: linear-gradient(
                                            to bottom right,
                                            var(--second__text),
                                            var(--text),
                                            var(--second__text)
                                        );
                                        background-clip: text;
                                        color: transparent;
                                    }
                                }

                                .dt-container {
                                    display: flex;
                                    align-items: center;
                                    gap: 0.5rem;

                                    @media screen and (width <= 460px) {
                                        width: 100%;
                                        display: grid;
                                        grid-template-columns: repeat(2, 1fr);
                                    }

                                    @media screen and (width <= 260px) {
                                        grid-template-columns: repeat(1, 1fr);
                                    }

                                    span {
                                        background: var(--back);
                                        padding: 0.5rem 1rem;
                                        border-radius: 8px;
                                        user-select: none;

                                        @media screen and (width <= 460px) {
                                            text-align: center;
                                        }

                                        small {
                                            font-size: var(--large);
                                            font-weight: bold;
                                            background: linear-gradient(
                                                to right,
                                                var(--red),
                                                var(--purple)
                                            );
                                            background-clip: text;
                                            color: transparent;

                                            @media screen and (width <= 348px) {
                                                display: block;
                                            }

                                            @media screen and (width <= 260px) {
                                                display: inline;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        .controls-container {
                            display: grid;
                            grid-template-columns: repeat(2, 1fr);
                            gap: 0.5rem;

                            @media screen and (width <= 600px) {
                                grid-template-columns: 1fr;
                            }

                            .control {
                                background: var(--back);
                                border-radius: 8px;
                                padding: 0.75rem;
                                height: max-content;

                                display: flex;
                                flex-direction: column;
                                gap: 0.5rem;

                                .header {
                                    display: flex;
                                    align-items: center;
                                    justify-content: space-between;
                                    cursor: pointer;
                                    user-select: none;

                                    h3 {
                                        background: linear-gradient(
                                            to bottom right,
                                            var(--second__text),
                                            var(--text),
                                            var(--second__text)
                                        );
                                        background-clip: text;
                                        color: transparent;
                                    }

                                    .controls-toggle-container {
                                        .toggle {
                                            width: 3rem;
                                            height: 22px;
                                            background: var(--red);
                                            border-radius: 11px;
                                            padding: 2px;
                                            cursor: pointer;
                                            display: flex;
                                            justify-content: start;
                                            transition: background 300ms 300ms;

                                            .toggle__circle {
                                                width: 18px;
                                                height: 18px;
                                                background: var(--text);
                                                border-radius: 50%;
                                                margin-left: 0.5px;
                                                transition: margin 500ms ease-in-out;
                                            }
                                        }
                                    }
                                }

                                .indicator {
                                    display: flex;
                                    align-items: center;
                                    user-select: none;

                                    h3 {
                                        color: var(--green);
                                        margin-right: 8px;
                                        font-size: var(--large);
                                    }

                                    span {
                                        display: inline;
                                        background: var(--green);
                                        margin-right: 3px;
                                        width: 4px;
                                        height: 4px;
                                        border-radius: 50%;
                                        animation: bounce 1s infinite ease-in-out;

                                        &:nth-child(1) {
                                            animation-delay: 0;
                                        }
                                        &:nth-child(2) {
                                            animation-delay: 0.2s;
                                        }
                                        &:nth-child(3) {
                                            animation-delay: 0.4s;
                                        }
                                        &:nth-child(4) {
                                            animation-delay: 0.6s;
                                        }
                                        &:nth-child(5) {
                                            animation-delay: 0.8s;
                                        }
                                    }
                                }
                            }

                            .speech.control {
                                grid-column: 1 / -1;

                                p {
                                    span {
                                        &:nth-child(1) {
                                            color: var(--second__text);
                                            font-weight: 700;
                                            text-decoration: underline;
                                            text-decoration-thickness: 2px;
                                            text-underline-offset: 2px;
                                        }
                                        &:nth-child(3) {
                                            color: var(--text);
                                        }
                                        &:nth-child(2),
                                        &:nth-child(4) {
                                            color: var(--red);
                                        }
                                    }
                                }

                                .buttons-container {
                                    display: flex;
                                    align-items: center;
                                    gap: 0.25rem;
                                    margin-left: auto;

                                    button {
                                        outline: none;
                                        border: 0;
                                        background: var(--second__back);
                                        color: var(--text);
                                        font-size: var(--medium);
                                        width: max-content;
                                        padding: 0.35rem 1.5rem;
                                        border-radius: 8px;
                                        cursor: pointer;

                                        &:hover {
                                            text-decoration: underline;
                                        }
                                    }
                                }
                            }

                            #toggle-listening:checked + .toggle {
                                background: var(--green);

                                & > .toggle__circle {
                                    margin-left: calc(3rem - 22px);
                                }
                            }
                            #toggle-talking:checked + .toggle {
                                background: var(--green);

                                & > .toggle__circle {
                                    margin-left: calc(3rem - 22px);
                                }
                            }
                        }

                        .stream-container {
                            display: flex;
                            flex-direction: column;
                            gap: 0.5rem;
                            align-items: center;
                            margin-top: 3rem;

                            .image-container {
                                width: 100%;
                                max-width: 600px;
                                aspect-ratio: 1.5 / 1;
                                background: var(--back);
                                border-radius: 8px;
                                overflow: hidden;

                                img {
                                    background: var(--back);
                                    width: 100%;
                                    height: 100%;
                                    object-fit: cover;
                                }
                            }

                            .led-intensity-slider {
                                width: 100%;
                                max-width: 600px;
                            }
                        }

                        footer {
                            width: 100%;
                            max-width: 600px;
                            text-align: center;
                            margin-top: auto;
                            padding-top: 3rem;
                            margin-inline: auto;

                            display: flex;
                            flex-direction: column;
                            align-items: center;

                            p {
                                width: 100%;
                                max-width: max-content;
                                font-size: var(--medium);
                                font-weight: bold;
                                background: linear-gradient(
                                    to right,
                                    var(--red),
                                    var(--purple),
                                    var(--red)
                                );
                                background-clip: text;
                                color: transparent;
                                user-select: none;
                            }
                        }
                    }
                }

                @keyframes bounce {
                    0%,
                    100% {
                        transform: translateY(-3px);
                    }
                    50% {
                        transform: translateY(6px);
                    }
                }
            </style>
        </head>

        <body>
            <section class="main">
                <div class="page-header">
                    <div class="page-header__top">
                        <h1 class="slogan">
                            EchoLens - Your Personalized Gateway to a Beautiful Life.
                        </h1>
                        <div class="toggle-container">
                            <input
                                hidden
                                id="show-hide-image"
                                name="show-hide-image"
                                type="checkbox"
                            />
                            <label class="toggle" for="show-hide-image">
                                <div class="toggle__circle"></div>
                            </label>
                            <div class="toggle-text">
                                <span>N</span>
                                <span>F</span>
                            </div>
                        </div>
                    </div>
                    <div class="page-header__bottom">
                        <div class="mode-toggle-container">
                            <input
                                hidden
                                id="dark-light-mode"
                                name="dark-light-mode"
                                type="checkbox"
                            />
                            <label class="toggle" for="dark-light-mode">
                                <div class="toggle__circle"></div>
                            </label>
                            <p id="dark-light-curr-mode">Dark</p>
                        </div>
                        <div class="dt-container">
                            <span id="date-container">Date: 2/15/2024</span>
                            <span id="time-container">Time: 14:17:51</span>
                        </div>
                    </div>
                </div>

                <div class="controls-container">
                    <div class="listening control">
                        <label for="toggle-listening" class="header">
                            <h3>Listen</h3>
                            <div class="controls-toggle-container">
                                <input
                                    hidden
                                    id="toggle-listening"
                                    name="toggle-listening"
                                    type="checkbox"
                                />
                                <label class="toggle" for="toggle-listening">
                                    <div class="toggle__circle"></div>
                                </label>
                            </div>
                        </label>
                        <div class="indicator" id="listening-indicator">
                            <h3>Recording Audio</h3>
                            <span></span>
                            <span></span>
                            <span></span>
                            <span></span>
                            <span></span>
                        </div>
                    </div>
                    <div class="talking control">
                        <label for="toggle-talking" class="header">
                            <h3>Talk</h3>
                            <div class="controls-toggle-container">
                                <input
                                    hidden
                                    id="toggle-talking"
                                    name="toggle-talking"
                                    type="checkbox"
                                />
                                <label class="toggle" for="toggle-talking">
                                    <div class="toggle__circle"></div>
                                </label>
                            </div>
                        </label>
                        <div class="indicator" id="talking-indicator">
                            <h3>Processing Image</h3>
                            <span></span>
                            <span></span>
                            <span></span>
                            <span></span>
                            <span></span>
                        </div>
                    </div>
                    <div class="speech control">
                        <p id="generated-text" class="generated-text">
                            <span>He/She said: </span>
                            <span>"</span>
                            <span id="generated-text-container">Hello...</span>
                            <span>"</span>
                        </p>
                        <div class="buttons-container">
                            <button class="generate-text" id="generate-text">Generate</button>
                            <button class="clear-generated-text" id="clear-generated-text">
                                Clear
                            </button>
                        </div>
                    </div>
                </div>

                <div id="stream-container" class="stream-container">
                    <div class="image-container">
                        <img id="stream-image" src="/" alt="** Stream Image **" />
                    </div>
                    <input
                        type="range"
                        min="0"
                        max="255"
                        value="125"
                        class="led-intensity-slider"
                        id="led-intensity-slider"
                    />
                </div>

                <footer>
                    <p>EchoLens | Smart Device - By Alpha-Amps</p>
                </footer>
            </section>
            <script>
                document.onreadystatechange = function () {
                    if (document.readyState == "complete") {
                        let baseHost = document.location.origin;
                        let streamUrl = baseHost + ":81/stream";
                        var xmlHttp = createXMLHttpObject();

                        /***** IMAGE GROUP (1) *****/
                        const imageCheckbox = document.getElementById("show-hide-image");
                        const viewStream = document.getElementById("stream-image");
                        viewStream.src = streamUrl;
                        const viewStreamContainer =
                            document.getElementById("stream-container");
                        const ledIntensitySlider = document.getElementById(
                            "led-intensity-slider"
                        );

                        /***** LISTENING GROUP (1) *****/
                        const listeningCheckbox = document.getElementById("toggle-listening");
                        const listeningIndicator = document.getElementById(
                            "listening-indicator"
                        );
                        let audioURL = null;
                        let chunks = [];
                        let recorder = null;
                        let canRecord = false;

                        /***** TALKING GROUP (1) *****/
                        const talkingCheckbox = document.getElementById("toggle-talking");
                        const talkingIndicator = document.getElementById("talking-indicator");

                        /***** TEXT GROUP (1) *****/
                        const generatedTextContainer = document.getElementById(
                            "generated-text-container"
                        );
                        const clearGeneratedTextButton = document.getElementById(
                            "clear-generated-text"
                        );
                        const generateTextButton = document.getElementById("generate-text");
                        let generatedText = null;
                        let isGenerating = false;

                        /***** DARK/LIGHT MODE (1) *****/
                        const toggleDarkLightMode =
                            document.getElementById("dark-light-mode");
                        const currentMode = document.getElementById("dark-light-curr-mode");

                        /* ========================================================================================= */

                        /***** IMAGE GROUP (2) *****/
                        handleCheckboxChange(imageCheckbox, viewStreamContainer);
                        imageCheckbox.addEventListener("change", () => {
                            listeningCheckbox.checked = false;
                            talkingCheckbox.checked = false;

                            handleCheckboxChange(listeningCheckbox, listeningIndicator);
                            handleCheckboxChange(talkingCheckbox, talkingIndicator);
                            handleCheckboxChange(imageCheckbox, viewStreamContainer);

                            handleToggleViewStream();
                        });
                        handleSliderIntensityUpdate();
                        ledIntensitySlider.oninput = handleSliderIntensityUpdate;

                        /***** LISTENING GROUP (2) *****/
                        setUpAudio();
                        handleCheckboxChange(listeningCheckbox, listeningIndicator);
                        listeningCheckbox.addEventListener("change", () => {
                            imageCheckbox.checked = false;
                            talkingCheckbox.checked = false;

                            handleCheckboxChange(imageCheckbox, viewStreamContainer);
                            handleCheckboxChange(listeningCheckbox, listeningIndicator);
                            handleCheckboxChange(talkingCheckbox, talkingIndicator);

                            if (canRecord && listeningCheckbox.checked) recorder.start();
                            else recorder.stop();

                            handleToggleListening();
                        });

                        /***** TALKING GROUP (2) *****/
                        handleCheckboxChange(talkingCheckbox, talkingIndicator);
                        talkingCheckbox.addEventListener("change", () => {
                            imageCheckbox.checked = false;
                            listeningCheckbox.checked = false;

                            handleCheckboxChange(imageCheckbox, viewStreamContainer);
                            handleCheckboxChange(listeningCheckbox, listeningIndicator);
                            handleCheckboxChange(talkingCheckbox, talkingIndicator);

                            handleToggleTalking();
                        });

                        /***** TEXT GROUP (2) *****/
                        updateButtonsState();
                        clearGeneratedTextButton.addEventListener(
                            "click",
                            handleClearButtonClick
                        );
                        generateTextButton.addEventListener("click", async () => {
                            try {
                                isGenerating = true;
                                updateButtonsState();
                                const transcription = await generateText(audioURL, "en-US");
                                console.log("Transcription:", transcription);
                            } catch (error) {
                                console.error("Error: ", error);
                            } finally {
                                isGenerating = false;
                                audioURL = null;
                                updateButtonsState();
                            }
                        });

                        /***** DARK/LIGHT MODE (2) *****/
                        toggleDarkLightMode.addEventListener("change", () => {
                            document.body.classList.toggle("light");

                            if (document.body.classList.contains("light")) {
                                currentMode.innerText = "Light";
                            } else {
                                currentMode.innerText = "Dark";
                            }
                        });

                        process();

                        /*****  FUNCTIONS HERE  *****/

                        function createXMLHttpObject() {
                            if (window.XMLHttpRequest) {
                                xmlHttp = new XMLHttpRequest();
                            } else {
                                xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
                            }
                            return xmlHttp;
                        }

                        function setUpAudio() {
                            if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
                                navigator.mediaDevices
                                    .getUserMedia({ audio: true })
                                    .then((stream) => {
                                        recorder = new MediaRecorder(stream);

                                        recorder.ondataavailable = (e) => {
                                            chunks.push(e.data);
                                        };

                                        recorder.onstop = (e) => {
                                            if (chunks.length > 0) {
                                                const blob = new Blob(chunks, {
                                                    type: "audio/ogg; codecs=opus",
                                                });
                                                chunks = [];
                                                audioURL = window.URL.createObjectURL(blob);
                                                updateButtonsState();
                                            }
                                        };

                                        canRecord = true;
                                    })
                                    .catch((err) => console.log(err));
                            }
                        }
                        async function generateText(audioURL, lang) {
                            const recognition = new webkitSpeechRecognition();
                            recognition.continuous = true;
                            recognition.interimResults = false;
                            recognition.lang = lang;
                            recognition.src = audioURL;

                            recognition.start();

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

                                    console.log("Final transcript: ", finalTranscript);
                                    resolve(finalTranscript);
                                };

                                recognition.onerror = function (event) {
                                    console.error("Speech recognition error: ", event.error);
                                    reject(event.error);
                                };

                                recognition.onend = function () {
                                    console.log("Speech recognition ended");
                                };
                            });
                        }

                        function handleToggleViewStream() {
                            let xhttp = new XMLHttpRequest();
                            xhttp.open("PUT", "TOGGLE_VIEW_STREAM", false);
                            xhttp.send();
                        }
                        function handleToggleListening() {
                            let xhttp = new XMLHttpRequest();
                            xhttp.open("PUT", "TOGGLE_LISTENING", false);
                            xhttp.send();
                        }
                        function handleToggleTalking() {
                            let xhttp = new XMLHttpRequest();
                            xhttp.open("PUT", "TOGGLE_TALKING", false);
                            xhttp.send();
                        }
                        function handleSliderIntensityUpdate() {
                            let xhttp = new XMLHttpRequest();
                            xhttp.open(
                                "PUT",
                                "UPDATE_INTENSITY?intensity=" + this.value,
                                false
                            );
                            xhttp.send();
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

                        function updateButtonsState() {
                            if (!audioURL) {
                                generateTextButton.style.display = "none";
                            } else {
                                generateTextButton.style.display = "block";

                                if (isGenerating) {
                                    generateTextButton.innerText = "Generating...";
                                } else {
                                    generateTextButton.innerText = "Generate";
                                }
                            }

                            if (!generatedText) {
                                clearGeneratedTextButton.style.display = "none";
                            } else {
                                clearGeneratedTextButton.style.display = "block";
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

                        function handleClearButtonClick() {
                            generatedTextContainer.innerText = ".....";
                        }

                        function response() {
                            let xmlResponse;
                            let xmlDoc;
                            let message;

                            xmlResponse = xmlHttp.responseXML;
                            console.log(xmlResponse);

                            /* xmlDoc = xmlResponse.getElementsByTagName("StreamState");
                            message = xmlDoc[0].firstChild.nodeValue;
                            if (message == 0) imageCheckbox.checked = false;
                            else imageCheckbox.checked = true;

                            xmlDoc = xmlResponse.getElementsByTagName("ListeningState");
                            message = xmlDoc[0].firstChild.nodeValue;
                            if (message == 0) listeningCheckbox.checked = false;
                            else listeningCheckbox.checked = true;

                            xmlDoc = xmlResponse.getElementsByTagName("TalkingState");
                            message = xmlDoc[0].firstChild.nodeValue;
                            if (message == 0) talkingCheckbox.checked = false;
                            else talkingCheckbox.checked = true; */
                        }

                        function process() {
                            updateDateTime();

                            if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
                                xmlHttp.open("PUT", "xml", true);
                                xmlHttp.onreadystatechange = response;
                                xmlHttp.send(null);
                            }

                            setTimeout(process, 40);
                        }
                    }
                };
            </script>
        </body>
    </html>
)RAW";
