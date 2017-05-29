<?php require "./includes/partials/header.inc"; ?>	
<?php include "./includes/functions.inc"; ?>
<?php session_start(); ?>
<script type="text/javascript" src="js/script.js"></script>
<script> setTimeout(postRedirect, 2000); </script>
<?php 	$parkId = $_POST["parkId"];		
		$stars = $_POST['reviewStars'];
		$text = $_POST['postText'];
		$userId = $_SESSION['userId'];
		sqlInsertPost($parkId, $userId, $text, $stars); 
?>
<main>
	<section id='post-section'>
		<form id='redirect' method='post' action='item.php'>
		<?php echo "
			<input name='parkId' value='{$parkId}' hidden>
			<input name='location' value='{$_POST['location']}' hidden>
			<input name='starratingValue' value='{$_POST['starratingValue']}' hidden>
			" ?>
		</form>
		<div id='postsuccessful-container'>
			<div id='postsuccessful'> </div>
		</div>
	</section>
	<script type="text/javascript" src="js/script.js"></script>
</main>
</body>