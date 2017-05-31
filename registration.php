<!-- HEADER AND PHP STARTUP FUNCTIONS -->
<?php require "./includes/partials/header.inc"; 
   require "./includes/registration.inc";
   include "./includes/functions.inc"; 
   pageSetup(true, false, true, "Cameron Short"); 
   ?>

<!-- MAIN HTML -->
<html>
   <head>
      <title>Login</title>
      <link rel="stylesheet" type="text/css" href="css/registration.css">
      <link rel="stylesheet" type="text/css" href="css/stylesheet.css">
      <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
   </head>
   <header></header>
   <nav></nav>
   <body>
      <main>
         <section id="section1">
            <div class="regTopbar">
               <?php require "./includes/partials/navbar.inc"; ?>
               <div class="topbar-right">
               </div>
            </div>
            <!-- Login/Signin BOX -->
            <div id="loginbox">
               <!--<span class="close">&times;</span> ADD?-->
               <div class="selectBox">
                  <div class="loginSelect" id="loginSelect">
                     <h1>
                     <br>LOGIN 
                     <h1>
                  </div>
                  <div class="signinSelect" id = "signinSelect">
                     <h1>
                     <br>SIGN UP
                     <h1>
                  </div>
               </div>
               <!-- LOGIN Modal -->
               <div id="loginModal" class="modal">
                  <div class="imgcontainer">
                     <i class="fa fa-user-circle-o fa-5x" style = "font-size:180px;"></i>
                  </div>
                  <br>                 
                  <div class = "elsebox" >
                     <form action = "" method = "post" class = "formLogin" onsubmit="return validateLogin();">
                        <div id="usernameContainer">
                           <div id="usernameContainerInner">
                              <div id="usernameLabel"> USERNAME </div>
                              <div id = "loginInputField">
                                 <input id = "username1" type = "text" placeholder = "Username" name = "username1">
                              </div>
                           </div>
                        </div>
                        <br>
                        <div id="usernameContainer">
                           <div id="usernameContainerInner">
                              <div id="usernameLabel"> PASSWORD </div>
                              <div id = "loginInputField">
                                 <input id = "password1" type = "password" placeholder = "Password" name = "password1">
                              </div>
                           </div>
                        </div>
                        <br>
                        <div float = "left">
                           <br>
                           <input type = "submit" name = "submitL">
                        </div>
                     </form>
                  </div>
               </div>
               <!-- SIGN-IN Modal -->
               <div id="signupModal" class="modal">
                  <div class = "elsebox" >
                     <form action = "" method = "post" class = "formSignin" onsubmit="return validateSignin();">
                        <div id="signupContainer">
                           <div id="signupContainerInner">
                              <div id="usernameLabel"> FIRST NAME </div>
                              <div id = "loginInputField">
                                 <input id = "fname" type = "text" placeholder = "First Name" name = "fname">
                              </div>
                              <br><br><br><br>
                              <div id="usernameLabel"> LAST NAME </div>
                              <div id = "loginInputField">
                                 <input id = "lname" type = "text" placeholder = "Last Name" name = "lname">
                              </div>
                              <br><br><br><br>
                              <div id="usernameLabel"> USERNAME </div>
                              <div id = "loginInputField">
                                 <input id = "username2" type = "text" placeholder = "Username" name = "username2">
                              </div>
                              <br><br><br><br>
                              <div id="usernameLabel"> PASSWORD </div>
                              <div id = "loginInputField">
                                 <input id = "password2" type = "password" placeholder = "Password" name = "password2">
                              </div>
                              <br><br><br><br>
                              <div id="usernameLabel"> CONFIRM </div>
                              <div id = "loginInputField">
                                 <input id = "cpassword" type = "password" placeholder = "Confirm Password" name = "cpassword">
                              </div>
                              <br><br><br>
                              <input type = "submit" name = "submit2">
                           </div>
                        </div>
                     </form>
                  </div>
               </div>
            </div>
            <script src = "js/registration.js"></script>
         </section>
      </main>
   </body>
</html>
<!-- FOOTER INCLUDE -->
<?php require "./includes/partials/footer.inc"; ?>