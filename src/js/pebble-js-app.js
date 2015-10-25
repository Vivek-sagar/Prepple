var SET_ID = "18503207";

var count = Math.round(Math.random()*56);

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess() {
  // Construct URL
  var url = "https://api.quizlet.com/2.0/sets/" + SET_ID + "?client_id=GdkF83yMeP&whitespace=1";
  // + pos.coords.latitude + "&lon=" + pos.coords.longitude + '&appid=' + myAPIKey;

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);

      // Temperature in Kelvin requires adjustment
      var term = json.terms[count].term;
      console.log("Term is " + term);

      // Conditions
      var definition = json.terms[count].definition;      
      console.log("Definition is " + definition);
      
      // Assemble dictionary using our keys
      var dictionary = {
        "KEY_WORD": term,
        "KEY_DEFINITION": definition
      };

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
        function(e) {
          console.log("Weather info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
    }      
  );
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log("PebbleKit JS ready!");

    // Get the initial weather
    locationSuccess();
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('Received message: ' + JSON.stringify(e.payload));
    count = e.payload.KEY_COUNT;
    locationSuccess();
  }                     
);
