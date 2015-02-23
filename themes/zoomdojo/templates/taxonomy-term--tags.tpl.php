<div class="share-view">
<?php 
    $link = url($_GET['q'], array('absolute' => TRUE));
    $lang = 'und'; 
?>
    <!-- Share button begin -->
    <a href="<?php print $link; ?>" 
        class="btn btn-danger btn-share" 
        data-img="<?php print file_create_url($term->field_image[$lang][0]['uri']);?>"
        data-title="<?php print $term->name; ?> (ZoomDojo - cracking the Job Search Code for You)"
        data-desc="I think that you will find this article interesting. <?php print organization_manager_user_getViewName();  ?>">
            <?php print t('Share'); ?>
        <i id="share-btn"></i>
    </a>
    <!-- Share button end -->
</div>
<?php if ( !empty($term->description) ): ?>
    <div>
      <?php print $term->description; ?>
    </div>
<?php endif; ?>  

<!-- Expert speak region -->
<?php if ($region['expert_speak']): ?>
  <div class="expert-speak-wrapper">
    <?php print render($region['expert_speak']); ?>
  </div>
<?php endif; ?>
<!-- Expert speak region -->
