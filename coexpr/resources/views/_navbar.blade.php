<nav class="navbar navbar-default navbar-fixed-top topnav" role="navigation">
	<div class="container topnav">
		<div class="navbar-header">
			<button type="button" class="navbar-toggle" data-toggle="collapse"
					data-target="#bs-example-navbar-collapse-1">
				<span class="sr-only">Toggle navigation</span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
				<span class="icon-bar"></span>
			</button>

			<a class="navbar-brand topnav" href="{{ url('/') }}">{{ Config::get('app.name') }}</a>
		</div>

		<div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
			<ul class="nav navbar-nav navbar-right">
				<li><a href="{{ url('/#home') }}">Home</a></li>
				<li><a href="{{ url('/#team') }}">Team</a></li>
				<li><a href="{{ url('/#contact') }}">Contact</a></li>
			</ul>
		</div>
	</div>
</nav>
