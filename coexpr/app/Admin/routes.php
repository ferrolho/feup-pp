<?php

Route::get('', ['as' => 'admin.dashboard', function () {
	$view = View::make('admin.index', ['name' => 'Administrator']);
	$content = $view->render();

	return AdminSection::view($content, 'Dashboard');
}]);

Route::get('test', ['as' => 'admin.test', function () {
	exec('(cd programs && ./test.out) > /dev/null 2>&1 &');

	return redirect(route('admin.dashboard'));
}]);

Route::get('information', ['as' => 'admin.information', function () {
	$content = 'Define your information here.';
	return AdminSection::view($content, 'Information');
}]);
