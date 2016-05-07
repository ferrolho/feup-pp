<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Correlation extends Model {

	/**
	 * The attributes that are mass assignable.
	 *
	 * @var array
	 */
	protected $fillable = ['gene1', 'gene2', 'correlation'];

	/**
	 * The attributes that should be hidden for arrays.
	 *
	 * @var array
	 */
	protected $hidden = [];

}

