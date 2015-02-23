<div class="featured-jobs-wrapper industries">
    <div class="featured-jobs-desc">
        <button><span style="font-size: 13pt; font-family: Verdana, sans-serif; color: #993300;"><b onclick="App.singInPopup();">Sign In now</b></span></button> and Find hundreds of 2015 Internships. Are you interested in international internships? Looking for accounting, technology or arts internships?  Discover internships in New York, LA, and many more cities.
    </div>
    <?php if (!empty($industries)): ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
        <?php foreach ($industries as $industry): ?>
        
            <?php if ($user->uid > 0): ?>
            <a href="/<?php print $industry->url; ?>">
                <div class="zd-one-industry">
                    <div class="industry-title">
                        <h3><?php print $industry->title; ?></h3>
                    </div>
                    <div class="industry-img">
                        <img src="<?php print $industry->image; ?>" alt="<?php print $industry->title; ?>" width="242" height="138" />
                    </div>
                </div>
            </a>
            <?php else: ?>
            <a onclick="App.singInPopup();">
                <div class="zd-one-industry">
                    <div class="industry-title">
                        <h3><?php print $industry->title; ?></h3>
                    </div>
                    <div class="industry-img">
                        <img src="<?php print $industry->image; ?>" alt="<?php print $industry->title; ?>" width="242" height="138" />
                    </div>
                </div>
            </a>
             <?php endif; ?>
        <?php endforeach; ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
    <?php endif; ?>
</div>