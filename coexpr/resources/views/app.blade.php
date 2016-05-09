<!DOCTYPE html>

<html lang="en">

	@include('_head')

	<body>

		@include('_navbar')

		@yield('content')

		@include('_footer')

		@include('_scripts')

		@stack('scripts')

	</body>

</html>
