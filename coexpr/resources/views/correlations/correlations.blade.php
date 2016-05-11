@extends('app')

@section('content')

	<div id="content" class="container">
		<div class="row">

			<div id="loader">
				<div class="panel panel-default">
					<div class="sk-circle">
						<div class="sk-circle1 sk-child"></div>
						<div class="sk-circle2 sk-child"></div>
						<div class="sk-circle3 sk-child"></div>
						<div class="sk-circle4 sk-child"></div>
						<div class="sk-circle5 sk-child"></div>
						<div class="sk-circle6 sk-child"></div>
						<div class="sk-circle7 sk-child"></div>
						<div class="sk-circle8 sk-child"></div>
						<div class="sk-circle9 sk-child"></div>
						<div class="sk-circle10 sk-child"></div>
						<div class="sk-circle11 sk-child"></div>
						<div class="sk-circle12 sk-child"></div>
					</div>

					<h4>Loading...</h4>
				</div>
			</div>

			<div class="col-xs-12 col-md-offset-2 col-md-8">
				<div class="panel panel-primary">
					<div class="panel-heading">
						<h3 class="panel-title">Search filters</h3>
					</div>

					<div class="panel-body">
						<form>
							<div class="form-group">
								<label for="range-slider">Correlations range</label>

								<div class="col-xs-12">
									<input id="range-slider" type="text" data-slider-value="[{{ $from }}, {{ $to }}]">
								</div>
							</div>

							<div class="form-group">
								<p><strong>Order by</strong></p>

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

	var APP_URL = {!! json_encode(url('/')) !!};

	var rangeSlider = $('#range-slider').slider({
		id: "range-slider",
		min: -1,
		max: 1,
		step: 0.01,
		range: true,
		ticks: [-1, 0, 1],
		ticks_labels: ['-1', '0', '1']
	});

	var clipboard = new Clipboard('#share-url-btn');

	clipboard.on('success', function (e) {
		$('#share-url-btn').attr('title', 'Copied!').tooltip('fixTitle').tooltip('show');

		e.clearSelection();
	});

	$(document).ready(function () {

		$('#share-url').val(getShareUrl());

		$('#share-url-btn').mouseleave(function () {
			$('#share-url-btn').attr('title', 'Copy to clipboard').tooltip('fixTitle');
		});

		$('#range-slider').on('slideStop', function (e) {
			startLoading();

			var page = $('.pagination li.active').text();

			$.ajax({
				url: getAjaxUrl(page),
				dataType: 'json'
			}).done(function (data) {
				$('.ajax-data').html(data);
				doneLoading();
			}).fail(function () {
				alert('Failed to load page.');
			});

			e.preventDefault();
		});

		$('input:radio[name=orderOptions]').on('change', function (e) {
			startLoading();

			var page = $('.pagination li.active').text();

			$.ajax({
				url: getAjaxUrl(page),
				dataType: 'json'
			}).done(function (data) {
				$('.ajax-data').html(data);
				doneLoading();
			}).fail(function () {
				alert('Failed to load page.');
			});

			e.preventDefault();
		});

		$(document).on('click', '.pagination a', function (e) {
			startLoading();

			var page = $(this).attr('href').split('page=')[1];

			$.ajax({
				url: getAjaxUrl(page),
				dataType: 'json'
			}).done(function (data) {
				$('.ajax-data').html(data);
				doneLoading();
			}).fail(function () {
				alert('Failed to load page.');
			});

			e.preventDefault();
		});

	});

	function startLoading() {
		$('#loader').show();
	}

	function doneLoading() {
		$('#loader').hide();

		$('#share-url').val(getShareUrl());

		$('[data-toggle="tooltip"]').tooltip();
	}

	function getShareUrl() {
		var page = $('.pagination li.active').text();

		var url = APP_URL + getAjaxUrl(page);

		return url;
	}

	function getAjaxUrl(page) {
		var orderBy = $('input[name=orderOptions]:radio:checked').val();
		var range = rangeSlider.slider('getValue');
		var page = page || 1;

		var url = '/correlations/bladder/' + orderBy + '/' + range[0] + '/' + range[1] + '?page=' + page;

		//console.log(url);

		return url;
	}

</script>
@endpush
