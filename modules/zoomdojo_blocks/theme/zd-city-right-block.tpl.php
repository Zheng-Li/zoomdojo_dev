<div class="zd-city-blck-wrapper">
	<ul>
		<?php foreach($cities as $city): ?>
			<li>
				<a href="/<?php print drupal_get_path_alias('taxonomy/term/' . $city->tid); ?>">
					<?php print $city->name; ?>
				</a>
			</li>
		<?php endforeach; ?>
	</ul>
</div>