<div class='topbar'>
	<div class='topbar-left'>
		<div class='navigation-container'>
			<?php setNavbar()?>
		</div>
</div>
	<div class='topbar-right'>
		<div class='registration-container'>
			<a href='search.php' class='registration' id='leftBtn'>Search</a>
			<a href='search.php' class='registration' id='rightBtn'>
			<?php if(isset($_SESSION[ 'login_user'])){ echo $_SESSION[ 'login_user']; } ?>
			</a>
		</div>
	</div>
</div>