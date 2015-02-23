<div class="zd-expert-page container-fluid" id="zd-expert-page-list" data-scroll="<?php print $scroll; ?>">
	<?php if (!empty($entities)): ?>
		<?php foreach ($entities as $item): ?>
			<div class="row-fluid">
				<div class="span12">
					<h1>
						<?php print $item['name']; ?>
					</h1>
				</div>
				<?php foreach ($item['content'] as $row): ?>
                    <div class="span12 category">
                        <h3>
                            <?php print $row['categoryTitle']; ?>
                        </h3>
                    </div>
                    <?php foreach ($row['content'] as $entity): ?>
                        <div class="row-fluid">
                            <div class="span12 one-speak" id="<?php print $entity->strId; ?>">
                                <h3>
                                    <a href="<?php print $entity->url; ?>">
                                        <?php print $entity->title; ?>
                                    </a>
                                </h3>
                                <div class="description">
                                    <?php print $entity->description; ?>
                                </div>
                            </div>
                        </div>
                    <?php endforeach; ?>
				<?php endforeach; ?>
			</div>
		<?php endforeach; ?>
	<?php endif; ?>
</div>
