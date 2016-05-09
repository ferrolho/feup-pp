@extends('app')

@section('content')

	<div class="container" style="padding-top: 50px;">
		<div class="row">

			<div class="ajax-data" style="padding-top: 50px;">
				@include('correlations._correlations')
			</div>

		</div>
	</div>

@endsection

@push('scripts')
<script>

	$(window).on('hashchange', function () {
		if (window.location.hash) {
			var page = window.location.hash.replace('#', '');

			if (page == Number.NaN || page <= 0) {
				return false;
			} else {
				getItems(page);
			}
		}
	});

	$(document).ready(function () {
		$(document).on('click', '.pagination a', function (e) {
			getItems($(this).attr('href').split('page=')[1]);
			e.preventDefault();
		});
	});

	function getItems(page) {
		$.ajax({
			url: '?page=' + page,
			dataType: 'json',
		}).done(function (data) {
			$('.ajax-data').html(data);
			location.hash = page;
		}).fail(function () {
			alert('Failed to load page.');
		});
	}

</script>
@endpush
