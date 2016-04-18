<!DOCTYPE html>

<html lang="en">

	@include('_head')

	<link href="/css/coexpr/coexpr.css" rel="stylesheet">

	<body>

		@include('_navbar')

		@yield('content')

		@include('_footer')


				<!-- Scripts -->

		<!-- jQuery -->
		<script src="//cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>

		<!-- Bootstrap Core JavaScript -->
		<script src="//cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.1/js/bootstrap.min.js"></script>

	</body>

</html>
