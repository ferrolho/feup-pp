@extends('errors.error')

@section('content')

	<div class="intro-header">
		<div class="container">
			<div class="row">
				<div class="col-lg-12">
					<div class="intro-message">

						<h1>Error 404</h1>

						<h3>Page not found</h3>

						<hr class="intro-divider">

						<ul class="list-inline intro-social-buttons">
							<li>
								<a href="/" class="btn btn-default btn-lg">
									Back to {{ Config::get('app.name') }}
								</a>
							</li>
						</ul>

					</div>
				</div>
			</div>
		</div>
	</div>

@endsection
