<div class="col-xs-12 text-center">
	<div class="row">

		<div id="share-clipboard" class="col-xs-12 col-md-offset-4 col-md-4">
			<label for="share-url">Share this results page:</label>

			<div class="input-group">
				<input id="share-url" type="text" class="form-control" readonly>

			<span class="input-group-btn">
				<button id="share-url-btn" class="btn btn-default" type="button" data-clipboard-target="#share-url">
					<img class="clippy" src="/assets/clippy.svg" alt="Copy to clipboard">
				</button>
			</span>
			</div>
		</div>

		<div class="col-xs-12">
			<p class="text-info">{{ number_format($correlations->total()) }} results</p>

			{!! $correlations->links() !!}
		</div>

	</div>
</div>

<div class="col-xs-12 col-md-offset-3 col-md-6">

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
