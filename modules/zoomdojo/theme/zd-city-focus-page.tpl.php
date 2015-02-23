<div class="zd-city-focus-desc">
    So you want a job in New York? Or London? At Zoomdojo, we encourage job seekers to look widely and go to where the jobs are! Our City Guides are written by young professionals and interns who have worked, lived or are deeply familiar with the cities they have written about. So you get the inside scoop on what it’s like to work, live, play in a new city which you don’t know enough about but where the jobs may be located!
</div>
<div class="zd-city-focus-list">
    <?php foreach ($terms as $city): ?>
	<div>
        <div>
            <a href="/<?php print $city->url; ?>">
                <h3>
                    <?php print $city->name; ?>
                </h3>
                <div>
                    <img src="<?php print $city->src; ?>" width="253" height="253" />
                </div>
            </a>
        </div>
		<span class="feature-shadow"></span>
	</div>
    <?php endforeach; ?>
</div>