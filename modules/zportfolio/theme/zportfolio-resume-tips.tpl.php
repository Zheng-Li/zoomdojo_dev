<div class="zd-acc-wrapper">
    <?php if (!empty($items)): ?>
        <div class="accordion" id="zportfolio-tips">

        <?php foreach ($items as $tid => $type): ?>
          <?php foreach ($type as $sid => $section): ?>
            <div class="accordion-group <?php print $tid!=0?'hidden':'';?> section-<?php print $tid;?>">
                <div class="accordion-heading">
                    <a href="#<?php print $sid; ?>" data-toggle="collapse" data-parent="#zportfolio-tips" class="collapsed accordion-toggle" title="<?php print $section['title']; ?>">
                        <?php print $section['title']; ?>
                    </a>
                </div>
                <div id="<?php print $sid; ?>" class="accordion-body collapse">
                    <div class="accordion-inner">
                      <?php print $section['text']; ?>
                    </div>
                </div>
            </div>
          
          <?php endforeach; ?>
        <?php endforeach; ?>

        </div>

    <?php endif; ?>
</div>

