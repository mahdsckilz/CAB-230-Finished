



// Get the button that opens the modal
var login = document.getElementById("loginSelect");
// Get the modal
var modalL = document.getElementById('loginModal');

// Get the button that opens the modal
var signin = document.getElementById("signinSelect");
// Get the modal
var modalS = document.getElementById('signupModal');

// Open and switch between modals
login.onclick = function() {
	login.style.backgroundColor = "#ff8c19";
	signin.style.backgroundColor = "#ff9933";
    modalL.style.display = "block";
	modalS.style.display = "none";
}

signin.onclick = function() {
	signin.style.backgroundColor = "#ff8c19";
	login.style.backgroundColor = "#ff9933";
    modalS.style.display = "block";
	modalL.style.display = "none";
}


////----LOGIN-----------------------------------------------------------------------
var validateLogin = function() {
	var returnvar = 0;
	if(checkUsername1() === 0) returnvar++;
	if (checkPassword1() === 0) returnvar++;
	if(returnvar === 2) return true;
	return false;
}

function checkUsername1(){
	var str = document.getElementById('username1');
	val = 0;
	if(str.value.length < 1){
		str.placeholder = "Username Empty";
		str.classList.add('placeholderred');
		val = 1;
	} else{
		str.classList.remove('placeholderred');
	}
	return val;
}

function checkPassword1(){
	var str = document.getElementById('password1');
	var val = 0;
	if(str.value.length < 1){
		str.placeholder = "Password Empty";
		str.classList.add('placeholderred');
		val = 1;
	}
	return val;
}

////----SIGNIN-----------------------------------------------------------------------
var validateSignin = function() {
	var returnvar = 0;
	if(checkFName() === 0) returnvar++;
	if(checkLName() === 0) returnvar++;
	if(checkUsername2() === 0) returnvar++;
	if(checkPassword2() === 0) returnvar++;
	if (checkConfPassword() === 0) returnvar++;
	if(returnvar === 5) return true;
	return false;
}

function checkFName(){
	var str = document.getElementById('fname');
	var val = 0;
	if(str.value.length < 1){
		str.placeholder = "First Name Empty";
		str.classList.add('placeholderred');
		val = 1;
	} else{
		str.classList.remove('placeholderred');
	}
	return val;
}

function checkLName(){
	var str = document.getElementById('lname');
	var val = 0;
	if(str.value.length < 1){
		str.placeholder = "Last Name Empty";
		str.classList.add('placeholderred');
		val = 1;
	} else{
		str.classList.remove('placeholderred');
	}
	return val;
}


function checkUsername2(){
	var str = document.getElementById('username2');
	val = 0;
	if(str.value.length < 1){
		str.placeholder = "Username Empty";
		str.classList.add('placeholderred');
		val = 1;
	} else{
		str.classList.remove('placeholderred');
	}
	return val;
}

function checkPassword2(){
	var str = document.getElementById('password2');
	var val = 0;
	if(str.value.length < 1){
		str.placeholder = "Password Empty";
		str.classList.add('placeholderred');
		val = 1;
	} else{
		str.classList.remove('placeholderred');
	}
	return val;
}

function checkConfPassword(){
	var str = document.getElementById('cpassword');
	var str2 = document.getElementById('password2');
	var val = 0;
	if(str.value !== str2.value){
		str.placeholder = "Does not Match Password";
		str.classList.add('placeholderred');
		val = 1;
	} else if (str.value.length < 1){
		str.placeholder = "Password Confirmation Empty";
		str.classList.add('placeholderred');
		val = 1;
	} else{
		str.classList.remove('placeholderred');
	}
	return val;
}