<?php if (!empty($nodes)): ?>
    <div>
        <h2><?php print $cityName; ?></h2>
        <div>
            <ul>
                <?php foreach ($nodes as $node): ?>
                    <li><a href="/<?php print $node->url; ?>"><?php print $node->title; ?></a></li>
                <?php endforeach; ?>
            </ul>
        </div>
    </div>
<?php endif; ?>