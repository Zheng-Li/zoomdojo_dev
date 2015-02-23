<?php if (!empty($properties)): ?>
    <div>
        <h2><?php print $cityName; ?></h2>
        <div>
            <?php foreach ($properties as $item): ?>
                <div>
                    <span>
                        <?php if (!empty($item->name) && $item->name != '&nbsp;'): ?>
                            <?php print $item->name; ?> :
                        <?php endif; ?>
                    </span>
                    <span><?php print $item->value; ?></span>
                </div>
            <?php endforeach; ?>
        </div>
        <?php if (!empty($description)): ?>
            <div>
                <?php print $description; ?>
            </div>
        <?php endif; ?>
    </div>
<?php endif; ?>