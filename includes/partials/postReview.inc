<div id='post-review-outer' onclick='hideshowItemPost()'>
</div>
<form id='post-review' action='post.php' method='post' onsubmit='return reviewPostValidator()'>
	<?php echo "
		<input name='parkId' value='{$parkId}' hidden />
		<input name='location' value='{$location}' hidden />
		<input name='starratingValue' value='{$starratingValue}' hidden />
	"; ?>
	<input name='postReview' value='true' hidden />
	<input id='reviewStars' name='reviewStars' value='5' hidden />
	<div id='post-review-header'> YOUR REVIEW</div>
	<div id='post-review-rating'>
		<div class='post-review-stars' id='post-review-star1' onclick='reviewStar(1)' ></div>
		<div class='post-review-stars' onclick='reviewStar(2)' ></div>
		<div class='post-review-stars' onclick='reviewStar(3)' ></div>
		<div class='post-review-stars' onclick='reviewStar(4)' ></div>
		<div class='post-review-stars' onclick='reviewStar(5)' ></div>
	</div>
	<textarea id='post-review-body' name='postText'></textarea>
	<div id='review-post-error'>20 OR MORE WORDS ARE REQUIRED TO POST A REVIEW</div>
	<button type='submit' id='post-submit'>SUBMIT
	</button>
</form>