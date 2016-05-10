@extends('app')

@section('content')

	<div class="container" style="margin-top: 50px; padding-top: 50px;">
		<div class="row">

			<div class="col-xs-12 col-md-offset-3 col-md-6">
				<form>

					<div class="col-xs-12 text-center">
						<input id="range-slider" type="text" data-slider-value="[{{ $from }}, {{ $to }}]">
					</div>

					<div class="form-group">
						<p class="radio-inline"><strong>Order by:</strong></p>

						<label class="radio-inline">
							<input type="radio" name="orderOptions" id="radioAsc"
								   value="asc" {{ $orderBy === 'asc' ? 'checked' : '' }}>
							Ascending
						</label>

						<label class="radio-inline">
							<input type="radio" name="orderOptions" id="radioDesc"
								   value="desc" {{ $orderBy === 'desc' ? 'checked' : '' }}>
							Descending
						</label>
					</div>

				</form>
			</div>

			<div class="col-xs-12 text-center">
				<div id="loader">
					<div>
						<h1>Loading...</h1>
					</div>
				</div>
			</div>

			<div class="ajax-data">
				@include('correlations._correlations')
			</div>

		</div>
	</div>

@endsection

@push('scripts')
<script>

	var rangeSlider = $('#range-slider').slider({
		id: "range-slider",
		min: -1,
		max: 1,
		step: 0.01,
		range: true,
		ticks: [-1, 0, 1],
		ticks_labels: ['-1', '0', '1']
	});

	$(document).ready(function () {

		$('#range-slider').on('slideStop', function (e) {
			showLoading();

			$.ajax({
				url: getAjaxUrl(),
				dataType: 'json'
			}).done(function (data) {
				$('.ajax-data').html(data);
				hideLoading();
			}).fail(function () {
				alert('Failed to load page.');
			});

			e.preventDefault();
		});

		$('input:radio[name=orderOptions]').on('change', function (e) {
			showLoading();

			$.ajax({
				url: getAjaxUrl(),
				dataType: 'json'
			}).done(function (data) {
				$('.ajax-data').html(data);
				hideLoading();
			}).fail(function () {
				alert('Failed to load page.');
			});

			e.preventDefault();
		});

		$(document).on('click', '.pagination a', function (e) {
			showLoading();

			var page = $(this).attr('href').split('page=')[1];

			$.ajax({
				url: getAjaxUrl() + '?page=' + page,
				dataType: 'json'
			}).done(function (data) {
				$('.ajax-data').html(data);
				hideLoading();
			}).fail(function () {
				alert('Failed to load page.');
			});

			e.preventDefault();
		});

	});

	function showLoading() {
		$('#loader').show();
	}

	function hideLoading() {
		$('#loader').hide();
	}

	function getAjaxUrl() {
		var orderBy = $('input[name=orderOptions]:radio:checked').val();
		var range = rangeSlider.slider('getValue');

		var url = '/correlations/bladder/' + orderBy + '/' + range[0] + '/' + range[1];

		//console.log(url);

		return url;
	}

</script>
@endpush
