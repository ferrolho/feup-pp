@extends('app')

@section('content')

	<div id="content" class="container">
		<div class="row">

			<div class="col-xs-12">

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
	</div>

@endsection
