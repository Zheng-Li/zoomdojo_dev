<?php if (!empty($nodes)): ?>
    <div class="all-nodes-expert">
        <h3>
            <?php print t('What the Experts Say'); ?>
        </h3>
        <div class="list">
            <ul>
                <?php foreach ($nodes as $node): ?>
                    <li>
                        <a href="/<?php print $node->url; ?>">
                            <?php print $node->title; ?>
                        </a>
                    </li>
                <?php endforeach; ?>
            </ul>
        </div>
    </div>
<?php endif; ?>