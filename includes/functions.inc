<?php
	$parklist = [];
	$suburbs = [];
	$names = [];
	$location;
	$selectID;
	$starratingValue;
	$parkId;
	$parkName;
	$currentPark;
	$onstart = true;
	
	$searchBox;
	$resultsBox;
	$regBox;
	
	$dsn = 'mysql:dbname=recit;host=localhost';
	$user = 'root';
	$password = '';

	$database = new PDO($dsn, $user, $password);

/////////////////////////Page Setup Functions////////////////////////////

// Function to determine how a page will be setup
// $searchBool   - Determines whether the Search Button will be displayed
// $resultsBool  - Determines whether the Results Button will be displayed
// $regBool      - Determines if the user is logged in (signout) or not (login & Sign Up)
// $author		 - Shows the author of the page
function pageSetup($searchBool, $resultsBool, $regBool, $author){
	global $searchBox, $resultsBox, $regBox, $pageAuthor;
	$searchBox = $searchBool;
	$resultsBox = $resultsBool;
	$regBox = $regBool;
	$pageAuthor = $author;
}

// Determines what the Navbar will displayed
function setNavbar(){
	global $searchBox, $resultsBox, $location, $starratingValue;
	if ($searchBox){
		echo "<a href='search.php' class='registration' id='leftBtn2'> &lt;&lt; Search </a>";
	}
	if ($resultsBox){
		echo "
		<div class='registration' id='rightBtn2' onclick='resultsRedirect()'> &lt;&lt; Results </div>
		<form id='results-nav-form' action='results.php' method='post'>	
			<input name='location' value='$location' hidden />
			<input id='starValue' name='starValue' value='$starratingValue' hidden />
		</form>";
	}

	echo "</div>
	</div>
	<div class='topbar-right'>
	<div class='registration-container'>
	";

	if(!isset($_SESSION['login_user'])){
		echo "	<a href='registration.php' class='registration' id='leftBtn'>Login</a>
				<a href='registration.php' class='registration' id='rightBtn'>Sign Up</a>
				<form action='search.php' method='post'> </form>
			";
	}
	else{
		echo " <form action='search.php' method='post'>";
		echo " <button type='submit' name='logout' value='true' class='signOut' id='signOutBtn'> ";
		echo "Sign Out";
		echo "</button>";
		echo "</form>";
	}
	
}

// Destroys the session on SignOut
function destroySession(){
	session_destroy();
}

	
/////////////////////////SQL FUNCTIONS///////////////////////////////
	
//Retrieves matching Suburb or Name from the database that matches the users searchQuery
	function sqlParklist(){
		global $database, $location, $parklist;
		
		$sql = "SELECT * FROM parks WHERE Suburb = :location OR Name = :location";
		$stmt = $database->prepare($sql);
		$stmt->bindParam(":location", $location);
		$stmt->execute();

		if ($stmt->rowCount() > 0) {
			$parklist = $stmt->fetchAll();
		}

	}

// Builds the Datalist that Autofills the users searchquery by finding all park Names and Suburbs,
// removes duplicate entries and alphabetises the list.
	function sqlCreateDatalist(){

		global $database, $location, $suburbs, $names;
		$sql = "SELECT Suburb FROM parks";
		$stmt = $database->prepare($sql);
		$stmt->execute();

		if ($stmt->rowCount() > 0) {
			$suburbs = $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
		}	

		$sql = "SELECT Name FROM parks";
		$stmt = $database->prepare($sql);
		$stmt->execute();

		if ($stmt->rowCount() > 0) {
			$names = $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
		}

		$suburbs = array_unique($suburbs);
		$suburbs = array_values($suburbs);
		sort($suburbs);
		
		$names = array_unique($names);
		$names = array_values($names);
		
		echo "<datalist id='datalist'>";
		for ($i = 0; $i < count($suburbs); $i++){
			$suburbs[$i] = ucwords(strtolower($suburbs[$i]));
			echo "<option value='{$suburbs[$i]}'>";
		}
		for ($i = 0; $i < count($names); $i++){
			$names[$i] = ucwords(strtolower($names[$i]));
			$names[$i] = str_replace("'", "&#39;", $names[$i]);
		echo "<option value='{$names[$i]}'>";
		}		
		echo "</datalist>";	
	}
	
// Retrieves details on the selected park and binds it to the currentPark variable for the item.php page
	function sqlGetPark(){
		global $database, $location, $suburbs, $parkId, $currentPark;
		
		try {
			$currentPark = [];
			$sql = "SELECT * FROM parks WHERE parkId = :parkId";
			$stmt = $database->prepare($sql);
			$stmt->bindParam(":parkId", $parkId);
			$stmt->execute();
			
			if ($stmt->rowCount() > 0){
				$currentPark = $stmt->fetchAll();
			}	
		}
		catch (PDOException $e){
			echo "Error: " . $e->getMessage();
		}
	}


// Returns all the reviews in the database that park displayed on the item.php page
	function sqlGetReviews(){
		global $database, $currentPark;
		$sql = "SELECT * FROM reviews WHERE parkId = :parkId ORDER BY date ASC";
		$stmt = $database->prepare($sql);
		
		$stmt->bindParam(":parkId", $currentPark[0]['parkId']);
		
		$stmt->execute();
		
		if ($stmt->rowCount() > 0){
			return $stmt->fetchAll();
		}	
	}

//  Retrieves the corresponding user for each post in the database
	function sqlGetReviewUser($user){
		global $database;

		$sql = "SELECT * FROM users WHERE userid = :userid";
		$stmt = $database->prepare($sql);
		
		$stmt->bindParam(":userid", $user);
		
		$stmt->execute();
		
		if ($stmt->rowCount() > 0){
			return $stmt->fetch();
		}	
	}


// Inserts a successfully validated post into the database
	function sqlInsertPost($parkId, $userId, $text, $rating){
		global $database;

		$sql = "INSERT INTO reviews (userid, parkid, text, rating) VALUES (:userid, :parkid, :text, :rating)";
		$stmt = $database->prepare($sql);
		
		$stmt->bindParam(":parkid", $parkId);
		$stmt->bindParam(":userid", $userId);
		$stmt->bindParam(":text", $text);
		$stmt->bindParam(":rating", $rating);
		
		$stmt->execute();
		sqlStarsUpdateAverage($parkId);
	}
	

// Updates the parkId's star rating to the new average after the user posts
	function sqlStarsUpdateAverage($parkId){
		global $database;
		
		$sql = "
		UPDATE parks as target
		INNER JOIN
		(
			select Round(Avg(rating)) as rating
			FROM reviews
			WHERE parkid = :parkid
		) as review
		SET Stars = rating
		WHERE parkId = :parkid";
			
		$stmt = $database->prepare($sql);
		
		$stmt->bindParam(":parkid", $parkId);
		
		$stmt->execute();
	}
	
	
////////////////////////////////////////Search Page Functions ///////////////////////////////////////////////////////


// creates the encoded arrays for js validation on the search query
	function jsEncodes(){
		global $parklist, $location, $suburbs, $names;
		$jsparklist = json_encode($parklist);
		$jssearchQuery = json_encode($location);
		$jssuburbs = json_encode($suburbs);
		$jsnames = json_encode($names);
		
		echo "<script type='text/javascript'>
			var parklist = $jsparklist;
			var searchQuery = $jssearchQuery;
			var suburbs = $jssuburbs;
			var parkNames = $jsnames;
		</script>";
	}
	

////////////////////////////////////////Results Page Functions///////////////////////////////////////////////////////


// Compares two strings to see if they match. Returns 0 if they match.
	function cmpSuburb($a, $b){
		return strcmp($a["Suburb"], $b["Suburb"]);
	}

// Compares Suburbs and arranges alphabetically. If Suburbs match, compares Names and arranges alphabetically.
	function resultsArrange($a, $b){
		if($a['Suburb'] == $b['Suburb'])
		{
			return strcmp($a['Name'], $b['Name']);
		}
	return strcmp($a['Suburb'], $b['Suburb']);
	}

// Populates the results list on the results page. Creates a table where each row is a form that posts its parkid on submit.
	function populateResults(){
		global $location, $parklist, $starratingValue;
		$location = $_POST["location"];
		$starratingValue = $_POST["starValue"];
		$tempArray = [];
		usort($parklist, 'resultsArrange');							
		$searchQuery = strtoupper($location);
		sqlParklist();
		
		for ($i = 0; $i < count($parklist); $i++)
		{
			if ($searchQuery == ($parklist[$i]['Name']  || $searchQuery == $parklist[$i]['Suburb']) && $parklist[$i]['Stars'] >= $starratingValue){
				array_push($tempArray, $parklist[$i]);
			}
		}
		$parklist = [];
		$parklist = $tempArray;
		
		for ($i = 0; $i < count($parklist); $i++){	
			echo"
				<tr class='result-table-row' onclick='document.forms[$i + 1].submit()' style='cursor:pointer'>
				<form id='$i' method='post' action='item.php'>
				<input name='parkId' value='{$parklist[$i]['parkId']}' hidden>
				<input name='location' value='$location' hidden>
				<input name='starratingValue' value='$starratingValue}' hidden>
					<td>",
						$parklist[$i]['Suburb'],
					"	
					</td>
					<td>",
							$parklist[$i]['Name'],
					"</td>
					<td>
						<img class='result-stars' src='images/{$parklist[$i]['Stars']}stars.png'/>
					</td>
				</form>
				</tr>";
		};
	}	
	

////////////////////////////////////////////////Items Page Functions////////////////////////////////////////////////////////////////
	

// Prepares the information regarding the selected park for the item.php page to run properly
	function itemPage(){
		global $currentPark, $parkName, $parkId, $starratingValue, $location;
		$parkId = $_POST["parkId"];
		$starratingValue = $_POST["starratingValue"] - 1;
		$location = $_POST['location'];
		sqlGetPark();
		$parkName = $currentPark[0]['Name'];
	}


// Populates the review list that is displayed on the item page
	function reviewListPopulate(){
		global $currentPark;
		$reviewList = sqlGetReviews();
		if(count($reviewList) > 0){		
			for ($i = 0; $i < count($reviewList); $i++){
				$reviewerId = $reviewList[$i]['userid'];
				$reviewId = $reviewList[$i]['reviewid'];
				$itemStar = $reviewList[$i]['rating'];
				$reviewer = sqlGetReviewUser($reviewerId);
				echo "
					<div class='review' itemscope itemtype='http://schema.org/Review'>
						<div itemprop='itemReviewed' hidden>{$reviewId}</div> 
						<div class='review-author' itemprop='author'> Review by: {$reviewer['userN']} </div>
						<div class='review-text' itemprop='reviewBody'>{$reviewList[$i]['text']} </div>
						<div class='review-star-container' itemprop='reviewRating'>
							<img class='review-star' src='images/{$itemStar}stars.png' alt='Star'/>
						</div>
					</div>
				";
			}	
		}
		else{
			echo " 
				<div id='noreview'>
				No reviews are available for this park yet. <br>
				<br>
				Feel free to leave a review using the ADD REVIEW button.
				</div>";
		}
	}


// Checks to see if the user is logged in to allow or deny submitting a review post
	function postLoggedIn(){
		echo "<a id='review-post' href='#' onclick='return hideshowItemPost()'> ADD REVIEW </a>";
		if (isset($_SESSION['posting']) == true && $_SESSION['posting'] == true){
			echo "<script type='text/javascript'> postButtonEnabled(true); </script>";
		}
		else{
			echo "<script type='text/javascript'> 
				postButtonEnabled(false); 
				</script>";
		}
	}


	
?>