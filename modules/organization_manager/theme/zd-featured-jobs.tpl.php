<div class="featured-jobs-wrapper industries">
    <div class="featured-jobs-desc">
        Explore Zoomdojo's 2015 internship list. Hundreds of new postings in architecture internships, accounting internships, arts internships, IT internships, finance internships, engineering internships, marketing internships and more. Want more options? Do an in-depth job search at Zoomdojo.
    </div>
    <?php if (!empty($industries)): ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
        <?php foreach ($industries as $industry): ?>
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
        <?php endforeach; ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
    <?php endif; ?>
</div>