<!-- HEADER AND PHP STARTUP FUNCTIONS -->
<?php require "./includes/partials/header.inc";
	require "./includes/functions.inc";
	session_start();
	pageSetup(true, false, true, "Ian Maskell"); 
?>

<!-- MAIN HTML -->
<main id='results-main'>
	<section id='section1'>
		<?php require "./includes/partials/navbar.inc"; ?>
		<div id='logo-results-container'>		
			<img src='images/logo.png' id='logo-results' alt='logo'/>
		</div>
		<div id='results-title'>
			<div> SEARCH RESULTS </div>
		</div>
		<div class='resultsbar-outer'>
			<div class='resultsbar-container'>
				<div>
					<table id='result-table' class='result-table'>				
						<tr id='result-table-header'>
							<th id='table-col-suburb'>Suburb</th>
							<th id='table-col-address'>Name</th>
							<th id='table-col-rating'>Rating</th>
						</tr>
							<?php populateResults();
								jsEncodes(); 
							?>
					</table>
				</div>
			</div>
			<div id='googlemap-container'>
				<div id='map-subcontainer'>
					<div id='map'></div>
				</div>
			</div>
		</div>
	</section>
	<script type="text/javascript" src="js/script.js"></script>
	<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCL5jfMCAYpKVqezrKCIuTjb7LueNhpjgk&callback=createMap"></script>
</main>

<!-- FOOTER INCLUDE -->
<?php require "./includes/partials/footer.inc"; ?>
			
	

	
