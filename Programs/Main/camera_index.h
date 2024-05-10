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
                        --back: #c3bdbd;
                        --text: #181818;
                        --second__back: #9d9999;
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
                            }

                            .page-header__bottom {
                                font-size: var(--large);

                                display: flex;
                                align-items: center;
                                gap: 0.5rem;

                                @media screen and (width <= 600px) {
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

                                    @media screen and (width <= 600px) {
                                        width: 100%;
                                        display: grid;
                                        grid-template-columns: repeat(2, 1fr);
                                    }

                                    @media screen and (width <= 300px) {
                                        grid-template-columns: repeat(1, 1fr);
                                        margin-block: 0.75rem;
                                    }

                                    #language-form {
                                        display: flex;
                                        align-items: center;
                                        gap: 0.75rem;
                                        div {
                                            display: flex;
                                            align-items: center;

                                            input,
                                            label {
                                                cursor: pointer;
                                                user-select: none;
                                            }
                                        }
                                    }

                                    #empty {
                                        @media screen and (width <= 300px) {
                                            display: none;
                                        }
                                    }

                                    span {
                                        background: var(--back);
                                        padding: 0.5rem 1rem;
                                        border-radius: 8px;
                                        user-select: none;

                                        @media screen and (width <= 600px) {
                                            text-align: center;
                                        }

                                        @media screen and (width <= 300px) {
                                            display: flex;
                                            align-items: center;
                                            justify-content: center;
                                            gap: 0.5rem;
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

                            .speech.control,
                            .signs.control {
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

                            div {
                                background: var(--back);
                                border-radius: var(--small);
                                padding: 0.75rem 1.25rem;

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
                            <form id="language-form">
                                <div>
                                    <input
                                        type="radio"
                                        id="en"
                                        name="language"
                                        value="EN"
                                        checked
                                    />
                                    <label for="en">EN</label>
                                </div>
                                <div>
                                    <input type="radio" id="fr" name="language" value="FR" />
                                    <label for="fr">FR</label>
                                </div>
                                <div>
                                    <input type="radio" id="ar" name="language" value="AR" />
                                    <label for="ar">AR</label>
                                </div>
                            </form>
                            <div id="empty"></div>
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
                    <div class="speech control" id="speech-container">
                        <p id="generated-text-container" class="generated-text-container">
                            <span>He/She said: </span>
                            <span>"</span>
                            <span id="generated-text">Hello...</span>
                            <span>"</span>
                        </p>
                        <div class="buttons-container">
                            <button class="clear-generated-text" id="clear-generated-text">
                                Clear
                            </button>
                        </div>
                    </div>
                    <div class="signs control" id="signs-container">
                        <p id="sign-text-container" class="sign-text-container">
                            <span>You said: </span>
                            <span>"</span>
                            <span id="sign-text">Hello...</span>
                            <span>"</span>
                        </p>
                        <div class="buttons-container">
                            <button class="clear-sign-text" id="clear-sign-text">Clear</button>
                            <button class="play-sign-text" id="play-sign-text">Play</button>
                        </div>
                    </div>
                </div>

                <footer>
                    <div>
                        <p>EchoLens | Smart Device - By Alpha-Amps</p>
                    </div>
                </footer>
            </section>
            <script>
                document.onreadystatechange = function () {
                    if (document.readyState == "complete") {
                        //===>
                        const languageForm = document.getElementById("language-form");
                        let selectedLanguage = "EN";
                        const speechLanguages = { EN: "en-US", FR: "fr-FR", AR: "ar-SA" };

                        //===>
                        const listeningCheckbox = document.getElementById("toggle-listening");
                        const listeningIndicator = document.getElementById(
                            "listening-indicator"
                        );

                        //===>
                        const talkingCheckbox = document.getElementById("toggle-talking");
                        const talkingIndicator = document.getElementById("talking-indicator");

                        //===>
                        const speechContainer = document.getElementById("speech-container");
                        const generatedTextContainer =
                            document.getElementById("generated-text");
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
                        const toggleDarkLightMode =
                            document.getElementById("dark-light-mode");
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
                            xhttp.open(
                                "PUT",
                                "GET_SELECTED_LANG?lang=" + selectedLanguage,
                                false
                            );
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
                            if (signText && signText !== "_EMPTY_") {
                                signTextContainer.innerText = signText;
                                signsContainer.style.display = "flex";
                            } else {
                                signsContainer.style.display = "none";
                            }
                        }

                        function handleToggleListening(listeningState) {
                            let xhttp = new XMLHttpRequest();
                            xhttp.open(
                                "PUT",
                                "TOGGLE_LISTENING?state=" + listeningState,
                                false
                            );
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
            </script>
        </body>
    </html>
)RAW";
