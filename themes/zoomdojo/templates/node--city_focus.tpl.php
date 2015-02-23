<?php $lang = 'und'; ?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>



  <?php if ($display_submitted): ?>
    <div class="meta submitted">
      <?php print $user_picture; ?>
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content clearfix"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
    ?>

    <?php if ($teaser): ?>
      <div>
        <?php if ( !empty($node->field_image[$lang][0]) ) : ?>
          <div class="image-<?php print $zebra; ?>">
            <?php
              $image = field_view_value('node', $node, 'field_image', $node->field_image[$lang][0]);
              print render($image);
            ?>
          </div>
        <?php endif; ?>
		
    		<?php print render($title_prefix); ?>
    			<?php if (!$page): ?>
    				<h2<?php print $title_attributes; ?>>
    				  <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    				</h2>
    			<?php endif; ?>
    		<?php print render($title_suffix); ?>
		
        <?php if ( !empty($node->field_teaser[$lang][0]) ) : ?>
          <div>
            <?php
              $description = field_view_value('node', $node, 'field_teaser', $node->field_teaser[$lang][0]);
              print render($description);
            ?>
          </div>
        <?php endif; ?>
      </div>
    <?php else: ?>
      <div>
        <div class="share-view">
        <?php 
            $link = url($_GET['q'], array('absolute' => TRUE));
            $description = '';
            if ( !empty($node->field_teaser[$lang][0]) ) {
              $description = $node->field_teaser[$lang][0]['value'];
            }
            $titlePrefix = $node->field_tags[$lang][0]['taxonomy_term']->name . ' ';
        ?>
            <!-- Share button begin -->
            <a href="<?php print $link; ?>" 
                class="btn btn-danger btn-share" 
                data-img="<?php print file_create_url($node->field_image[$lang][0]['uri']);?>"
                data-title="<?php print $titlePrefix . $title; ?> (ZoomDojo - cracking the Job Search Code for You)"
                data-desc="I think that you will find this article interesting. <?php print organization_manager_user_getViewName();  ?>">
                    <?php print t('Share'); ?>
                <i id="share-btn"></i>
            </a>
            <!-- Share button end -->
        </div>
        <?php if ( !empty($node->body[$lang][0]) ) : ?>
          <div>
            <?php
              $body = field_view_value('node', $node, 'body', $node->body[$lang][0]);
              print render($body);
            ?>
          </div>
        <?php endif; ?>
        <?php if ( !empty($node->field_additional_body[$lang][0]) ) : ?>
          <div>
            <?php
              $field_additional_body = field_view_value('node', $node, 'field_additional_body', $node->field_additional_body[$lang][0]);
              print render($field_additional_body);
            ?>
          </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

  </div>

  <?php
    // Remove the "Add new comment" link on the teaser page or if the comment
    // form is being displayed on the same page.
    if ($teaser || !empty($content['comments']['comment_form'])) {
      unset($content['links']['comment']['#links']['comment-add']);
    }
    // Only display the wrapper div if there are links.
    $links = render($content['links']);
    if ($links):
  ?>
    <div class="link-wrapper">
      <?php print $links; ?>
    </div>
  <?php endif; ?>

  <?php print render($content['comments']); ?>

</div>
