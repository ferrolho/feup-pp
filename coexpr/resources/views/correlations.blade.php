@extends('app')

@section('content')

	<div class="container" style="padding-top: 50px;">
		<div class="row">

			<div class="col-xs-12 col-md-offset-3 col-md-6" style="padding-top: 50px;">

				{{--<p>Showing {{ $correlations->perPage() }} of {{ $correlations->total() }} results.</p>--}}
				<p class="text-center">{{ $correlations->total() }} results</p>

				<div class="table-responsive">
					<table class="table table-bordered table-hover table-striped">

						<thead>
							<tr>
								<th>#</th>
								<th>Gene 1</th>
								<th>Gene 2</th>
								<th>Correlation</th>
							</tr>
						</thead>

						<tbody>

							@foreach ($correlations as $correlation)

								<tr>
									<th scope="row">{{ $correlation->id }}</th>
									<td>{{ $correlation->gene1 }}</td>
									<td>{{ $correlation->gene2 }}</td>
									<td>{{ $correlation->correlation }}</td>
								</tr>

							@endforeach

						</tbody>

					</table>
				</div>
			</div>

			<div class="text-center">
				{!! $correlations->links() !!}
			</div>

		</div>
	</div>

@endsection
