@extends('app')

@section('content')

	<div id="content" class="container">
		<div class="row">

			<h1 class="text-center">Tissues</h1>

			<hr>

			<ul id="tissues-list" class="list-unstyled">
				@foreach($tissues as $tissue)
					<li><a href="/explorer/{{ str_slug($tissue) }}">{{ $tissue }}</a></li>
				@endforeach
			</ul>

			<hr>

		</div>
	</div>

@endsection
