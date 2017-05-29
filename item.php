<!-- HEADER AND PHP STARTUP FUNCTIONS -->
<?php require "./includes/partials/header.inc";
	include "./includes/functions.inc";
	session_start();
	pageSetup(true, true, true, "Ian Maskell");
	itemPage(); 
?>

<!-- MAIN HTML -->
	<main>
		<div id='section1'>
		<?php require "./includes/partials/navbar.inc"; ?>
		<?php require "./includes/partials/postReview.inc"; ?>
			<div id='logo-results-container'>	
				<img src='images/logo.png' id='logo-results' alt='logo'/>
			</div>
			<div class='item-container-outer'>
				<div class='item-container'>
					<div>
						<div id='item-title'>
							<div> <?php echo "$parkName" ?> </div>
						</div>
						<div id='item-map-container'>
							<div id='map'>
							</div>
						</div>
						<form id='item-review-container'>
							<div id='review-title'>Reviews </div>
							<div id='review-list'>
								<?php reviewListPopulate(); ?>
							</div>
								<div id='post-login-error'> YOU MUST LOGIN BEFORE POSTING A REVIEW</div>
								<?php postLoggedIn(); ?>
						</form>
					</div>
				</div>
			</div>
		</div>
		<script type="text/javascript" src="js/script.js"></script>
		<script type='text/javascript'>
			var parklist = <?php echo json_encode($currentPark) ?>;
		</script>
		<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCL5jfMCAYpKVqezrKCIuTjb7LueNhpjgk&callback=createMap"></script>
	</main>

<!-- FOOTER INCLUDE -->
<?php require "./includes/partials/footer.inc"; ?>