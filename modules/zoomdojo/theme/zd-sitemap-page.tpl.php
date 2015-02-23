<div class="accordion" id="accordion-site-map">
    <?php foreach($siteMap as $key => $map): ?>
        <?php if (!empty($map->items)): ?>
            <div class="accordion-group">
                <div class="accordion-heading">
                    <a class="accordion-toggle" data-toggle="collapse" data-parent="#accordion2" href="#collapse-<?php print $key; ?>">
                        <?php print $map->title; ?>
                    </a>
                </div>
                <div id="collapse-<?php print $key; ?>" class="accordion-body collapse in">
                    <div class="accordion-inner">
                        <ul>
                            <?php foreach($map->items as $item): ?>
                                <li>
                                    <a href="/<?php print $item->url; ?>"><?php print $item->title; ?></a>
                                </li>
                            <?php endforeach; ?>
                        </ul>
                    </div>
                </div>
            </div>
        <?php endif; ?>
    <?php endforeach; ?>
</div>