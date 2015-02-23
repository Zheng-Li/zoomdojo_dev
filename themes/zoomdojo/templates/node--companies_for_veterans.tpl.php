<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="meta submitted">
      <?php print $user_picture; ?>
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <?php if (!$teaser): ?>
      <div class="share-view">
          <?php
            $link = url($_GET['q'], array('absolute' => TRUE));
          ?>
          <!-- Share button begin -->
          <a href="<?php print $link; ?>"
             class="btn btn-danger btn-share"
             data-img=""
             data-title="<?php print $title; ?> (ZoomDojo - cracking the Job Search Code for You)"
             data-desc="I think that you will find this article interesting. <?php print organization_manager_user_getViewName();  ?>">
              <?php print t('Share'); ?>
              <i id="share-btn"></i>
          </a>
          <!-- Share button end -->
      </div>
    <!-- Expert speak region -->
    <?php if ($region['expert_speak']): ?>
      <div class="expert-speak-wrapper">
        <?php print render($region['expert_speak']); ?>
      </div>
    <?php endif; ?>
    <!-- Expert speak region -->
  <?php endif; ?>

  <div class="content clearfix"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
      print $search_results;
    ?>
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
