<?php
session_start();	
$servername = "localhost";
$username   = "root";
$password   = "";
$dbname     = "recit";
$conn       = new PDO('mysql:host=' . $servername . ';dbname=' . $dbname, $username, $password);

if (isset($_POST['submitL']) && !empty($_POST['username1']) && !empty($_POST['password1'])) {
    
    
    $username = $_POST['username1'];
    $password = $_POST['password1'];
    $stmt     = $conn->prepare("SELECT userN FROM users WHERE userN=:username "); // AND passW=:hash_password
    $stmt->bindParam('username', $username, PDO::PARAM_STR);
    $stmt->execute();
    $count = $stmt->rowCount();
    $data  = $stmt->fetch(PDO::FETCH_OBJ);
    if ($count) {
        $userTemp = $data->userN;
        
        $stmt = $conn->prepare("SELECT userid, passW FROM users WHERE userN=:username ");
        $stmt->bindParam('username', $username, PDO::PARAM_STR);
        $stmt->execute();
        $count = $stmt->rowCount();
        $data  = $stmt->fetch(PDO::FETCH_OBJ);
        if (password_verify($password, $data->passW)) {	
			$_SESSION['login_user'] = $userTemp;
			$_SESSION['posting'] = true;
			$_SESSION['userId'] = (string)$data->userid;
            header('Location: search.php');
        }
    }
    
}

if (isset($_POST['submit2'])) {
    
    $fname    = $_POST['fname'];
    $lname    = $_POST['lname'];
    $username = $_POST['username2'];
    $password = password_hash($_POST['password2'], PASSWORD_BCRYPT);
    $stmt     = $conn->prepare("INSERT INTO users (firstN, lastN, userN, passW) VALUES ('$fname', '$lname', '$username', '$password')");
    $stmt->bindParam('fname', $username, PDO::PARAM_STR);
    $stmt->bindParam('lname', $username, PDO::PARAM_STR);
    $stmt->bindParam('username', $username, PDO::PARAM_STR);
    $stmt->bindParam('password', $username, PDO::PARAM_STR);
    $stmt->execute();
    $_SESSION['login_user'] = $username;
	$_SESSION['posting'] = true;
    header('Location: search.php');
}

?>