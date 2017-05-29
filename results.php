<?php require "./includes/partials/header.inc"; ?>	
<?php include "./includes/functions.inc";?>
<?php session_start();
pageSetup(true, false, true, "Ian Maskell"); ?>
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
							<?php populateResults(); ?>
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
<script type='text/javascript'>
	var parklist = <?php echo json_encode($parklist) ?>;
	var searchQuery = <?php echo json_encode($location) ?>;
	var suburbs = <?php echo json_encode($suburbs) ?>;
</script>
	<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCL5jfMCAYpKVqezrKCIuTjb7LueNhpjgk&callback=createMap"></script>
</main>
<?php require "./includes/partials/footer.inc"; ?>
			
	

	
