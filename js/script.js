var	searchbarInput = document.getElementById("searchbar-input"),
	starratingValue = document.getElementById("starrating-value"),
	searchbarButton = document.getElementById("searchbar-button");
	resultsForm = document.getElementById("results-nav-form");
var geolocation = false;
var lat,
	lng,
	validation,
	parklist,
	suburbs,
	parkNames,
	marker;
var starValue = document.getElementById("starValue");
var hidePost = false;

function resultsRedirect(){
	resultsForm.submit();
}

function postRedirect(){
	document.getElementById("redirect").submit();
}



// SEARCHPAGE FUNCTIONS //

// Validates the search input to see if it matches a known suburb or parkname.
// OUTPUT: Returns true if query matches, false if query doesn't match.
function searchQueryValidate(){
	for (var i = 0; i < suburbs.length; i++){
		if (searchbarInput.value.toUpperCase() == suburbs[i].toUpperCase()){
			return true;
		}
	}	
	for (var i = 0; i < parkNames.length; i++){
		if (searchbarInput.value.toUpperCase() == parkNames[i].toUpperCase()){
			return true;
		}
	}
	searchbarInput.style.color = "red";
	searchbarInput.value = "Invalid Search Request";
	searchbarButton.disabled = true;
    return false;
}


//Returns input text color to default
function searchInputKey(){
	var list = document.getElementById("datalist");
	searchbarInput.style.color = "black";
	searchbarButton.disabled = false;
	if (searchbarInput.value.length < 3){
		searchbarInput.setAttribute("list", "");
	}
	else {
		list.children.disabled = false;
		searchbarInput.setAttribute("list", "datalist");
	}
}


//Changes Elements when Search radio button is selected
function searchRadioBtn(){
	searchbarInput.readOnly = false;
	geolocation = false;
	searchbarInput.style.backgroundColor = "#fff";
	searchbarInput.value = "All Locations";
}


//Changes Elements when Geolocation radio button is selected
function geoRadioBtn(){
	searchbarInput.readOnly = true;
	geolocation = true;
	searchbarInput.style.color = "black";
	searchbarInput.style.backgroundColor = "#ddd";
	getGeolocation();
}


// When a user selects a star it enables selected star and higher, and disables all lower.
// Also changes the label field value.
function starChange(star){
	starNumber = star;
	var starButtons = document.getElementsByClassName("stars");
	
	for (var i = 0; i < starNumber ; i++){
		starButtons[i].style.backgroundImage = "url('../CAB230-Project/images/starfull.png')";
		if (starNumber == 1){
			starratingValue.innerHTML = "ANY RATING";
			starValue.value = 0;
			starButtons[i].style.backgroundImage = "url('../CAB230-Project/images/starempty.png')";
		}
		
		else if(starNumber == 5)
		{
			starratingValue.innerHTML = (starNumber) + " STARS";
			starValue.value = 5;
		}
		
		else{
			starratingValue.innerHTML = (starNumber) + "+ STARS";
			starValue.value = starNumber;
		}
	}
	for (var j = starNumber; j < 5; j++){
		starButtons[j].style.backgroundImage = "url('../CAB230-Project/images/starempty.png')";
	}	
}


// Gets geolocation information based on current location.
function getGeolocation(){
	if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(showGeolocation);
    } 
	else{
        console.log("Geolocation not supported");
    }
}


// Shows Geolocation information from the argument in the getGeolocation function
function showGeolocation(position){
	lat = position.coords.latitude;
	lng = position.coords.longitude;
	console.log("Latitude: " + lat);
	console.log("Longitude: " + lng);
	getReverseGeocodingData(lat, lng);
}


// Ensures the value is available on async end
function finishGeo(addr){
	searchbarInput.value = addr;
}


// Gets the Location using google reverse geocoding API.
function getReverseGeocodingData(lat, lng) {
    var latlng = new google.maps.LatLng(lat, lng);
    // This is making the Geocode request
    var geocoder = new google.maps.Geocoder();
    geocoder.geocode({ 'latLng': latlng }, function (results, status) {
        if (status !== google.maps.GeocoderStatus.OK) {
            alert(status);
        }
        // This is checking to see if the Geoeode Status is OK before proceeding
        if (status == google.maps.GeocoderStatus.OK) {
			console.log(results[0].formatted_address);
            var address = results[0].address_components[2]['long_name'];
			finishGeo(address);			
        }
    });
}


// ITEM FUNCTIONS

// Shows and hides the create Review box on the Item Page.
function hideshowItemPost(){
	hidePost = !hidePost;
	if (!hidePost){
		document.getElementById('post-review-outer').style.visibility = 'hidden';
		document.getElementById('post-review').style.visibility = 'hidden';
	}
	else{
		document.getElementById('post-review-outer').style.visibility = 'visible';
		document.getElementById('post-review').style.visibility = 'visible';
	}
}


// Changes the style of the ADD REVIEW button depending of whether the user is logged in.
function postButtonEnabled(enabled){
	reviewPost = document.getElementById('review-post');
	if (enabled == true){
		reviewPost.style.backgroundColor = '#ff9933';
	}
	else{
		reviewPost.style.backgroundColor = '#aaa';
		reviewPost.style.color = 'black';
		reviewPost.style.borderColor = 'grey';
		reviewPost.onclick = showPostLoginError;
}


// Display error message if user selects ADD REVIEW when not signed in.
function showPostLoginError(){
	errorMsg = document.getElementById('post-login-error');
	errorMsg.className = "show";
	setTimeout(function(){
		errorMsg.className = errorMsg.className.replace("show", ""); }, 3000);
	}	
}


// 
function reviewStar(star){
	starObject = document.getElementsByClassName('post-review-stars');
	document.getElementById('reviewStars').value = star;

	for (var i = 5; star < i; i--){
		starObject[i - 1].style.backgroundImage = "url('../CAB230-Project/images/starempty.png')";
	}

	for (var i = 0; i < star; i++){
		starObject[i].style.backgroundImage = "url('../CAB230-Project/images/starfull.png')";	
	}
}

function reviewPostValidator(){
	var reviewText = document.getElementById('post-review-body');
	if( reviewText.value.length > 19){
		return true;
	}
	else{
		errorMsg = document.getElementById('review-post-error');
		errorMsg.className = "show";
		setTimeout(function(){
		errorMsg.className = errorMsg.className.replace("show", ""); }, 3000);
		return false;
	}
}

function postRedirect(){
	document.getElementById("redirect").submit();
}


// MAP FUNCTIONS //

//Takes all location positions in parklist array and finds the center position.
//OUTPUT: Returns latlngCenter array with latitude, and longitude values.
function mapCenter(){
	var latAvg = 0;
	var lngAvg = 0;
	var latlngCenter;
	
	for (i = 0; i < parklist.length; i++){
		latAvg = latAvg + parseFloat(parklist[i]['Latitude']);
		lngAvg = lngAvg + parseFloat(parklist[i]['Longitude']);
	}	
	latAvg = latAvg / parklist.length;
	lngAvg = lngAvg / parklist.length;
		
	latlngCenter = [latAvg, lngAvg];
	return latlngCenter;
}


//Creates the map that is focused to the area of the results from the parklist array.
function createMap(){
	var latlngCenter = mapCenter();	
	var mapOptions = {
		center: new google.maps.LatLng(latlngCenter[0], latlngCenter[1]),
		zoom: 13,
		mapTypeId: google.maps.MapTypeId.ROADMAP,
		streetViewControl: false
	}
	var map = new google.maps.Map(document.getElementById('map'), mapOptions);
	mapCreatePins(map);
}


//Creates Pins on the created map for each park inside the parklist Array.
//Input: 'map' is the object map the pins will be placed on.
function mapCreatePins(map){
	var bounds = new google.maps.LatLngBounds();
	for (i = 0; i < parklist.length; i++){
			x = i;
			title = parklist[i]['Name'];
			var position = new google.maps.LatLng(parseFloat(parklist[i]['Latitude']), parseFloat(parklist[i]['Longitude']))
			var marker = new google.maps.Marker({
				id: parklist[i]['parkId'],
				map: map,
				draggable: false,
				animation: google.maps.Animation.DROP,
				position: position,
				title: title
			});			
			
			url = window.location.href;
			var patt = new RegExp('results.php');		
			
			// Creates the Link on the map pins that match the list on the left.
			if (patt.test(url)){
				google.maps.event.addListener(marker, 'click', (function(marker, i) {
					return function() {
						document.forms[i + 1].submit();
					}
				})(marker, i));
			}				
			bounds.extend(position);
	}
	if (parklist.length > 3){
		map.fitBounds(bounds);
	}
}


