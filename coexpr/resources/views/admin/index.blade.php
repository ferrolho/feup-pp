<div class="row">

	<div class="col-lg-12">
		<h1 class="page-header">Hello, {{ $name }}!</h1>
	</div>

	<div class="col-lg-3 col-md-6">
		<div class="panel panel-primary">
			<div class="panel-heading">
				<div class="row">
					<div class="col-xs-3">
						<i class="fa fa-terminal fa-5x"></i>
					</div>

					<div class="col-xs-9 text-right">
						<div class="huge" style="font-size: 40px;">26</div>
						<div>Refresh DB</div>
					</div>
				</div>
			</div>

			<a href="{{ route('admin.test') }}">
				<div class="panel-footer">
					<span class="pull-left">Run script</span>
					<span class="pull-right"><i class="fa fa-arrow-circle-right"></i></span>
					<div class="clearfix"></div>
				</div>
			</a>
		</div>
	</div>

</div>
