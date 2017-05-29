<?php require "./includes/partials/header.inc"; ?>	
<?php include "./includes/functions.inc";?>
<?php
	session_start();
	if (isset($_POST['logout']) && $_POST['logout'] == true){
		session_destroy();
		session_start();
	}
	?>
<?php sqlCreateDatalist(); ?>
<?php	pageSetup(false, false, true, "Ian Maskell");
		jsEncodes();
?>

<main id='search-main'>
	<section id='section1'>
		<?php require "./includes/partials/navbar.inc"; ?>
		<div id='container-x'>
			<div id='logo-search-container'>		
				<img src='images/logo.png' id='logo-search' alt='logo'/>
			</div>
			<div id='searchtype'>
				<div class='searchtype-subdiv' id='subdiv1'>
					<input type='radio' value='search' name='education' class='searchtype-child' onClick='searchRadioBtn()' checked/>
					<label class='searchtype-label'>SEARCH </label>
				</div>
				<div class='searchtype-subdiv'>
					<input type='radio' value='geolocation' name='education' class='searchtype-child' onClick='geoRadioBtn()'/>
					<label class='searchtype-label'>GEOLOCATION</label>
				</div>
			</div>
			<script type="text/javascript" src="js/script.js"></script>	
			<form id='search-form' action='results.php' method='post' onsubmit='return searchQueryValidate()' autocomplete=off>
			<div class='searchbar-container'>
				<div>
						<input name='currentPage' value='results' hidden/>
						<input id='starValue' name='starValue' value=0 hidden/>
						<label id='searchbar-label'>
							SEARCH
						</label>
						<input name='location' id='searchbar-input' placeholder="Enter park name or suburb" onkeyup="searchInputKey()" autocomplete='off'/>
						<button type='submit' id='searchbar-button'>
						<i class='fa fa-search'></i>
						</button>
				</div>
			</div>
			<div id='rating-container'>
				<div id='rating-container-inner'>
					<div id='starrating-label'> RATING </div>
					<div id='star-container'>
						<div class='stars' onclick='starChange(1)' ></div>
						<div class='stars' onclick='starChange(2)' ></div>
						<div class='stars' onclick='starChange(3)' ></div>
						<div class='stars' onclick='starChange(4)' ></div>
						<div class='stars' onclick='starChange(5)' ></div>
					</div>
					<div id='starrating-value'> ANY RATING </div>
				</div>
			</div>
			</form>
		</div>
		<script type="text/javascript" src="js/script.js"></script>	
	</section>
</main>
<?php require "./includes/partials/footer.inc"; ?>
