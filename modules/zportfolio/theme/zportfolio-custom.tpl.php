<?php if (empty($js)): ?>
<?php foreach($sections as $sid=>$section): ?>
<?php
    if(!empty($error['new']) && isset($section['new'])) {
        $error = $error['new'];
    }
?>
<div class="accordion-group accordion-group-custom accordion-group-custom-<?php print $sid ?> <?php print isset($section['new'])?'new':'';?>" data-type="6" data-id="<?php print $sid ?>">
  <div class="accordion-heading">
    <div><a class="custom-delete"></a>
      <a class="custom-rename"></a></div>
      
      <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#custom-<?php print isset($section['new'])?'new-':'';?><?php print $sid; ?>">
          <?php print $section['title']; ?>
      </a>
      <input type="hidden" name="custom<?php print isset($section['new'])?'[new]':''; ?>[<?php print $sid; ?>][title]" value="<?php print $section['title']; ?>"/>
  </div>
  <div id="custom-<?php print isset($section['new'])?'new-':'';?><?php print $sid; ?>" class="accordion-body collapse">
      <div class="accordion-inner">
          <?php
              $class = 'hide';
              $hideSaveBtn = true;
              if (isset($section['items']) && count($section['items']) > 0) {
                  $class = '';
                  $hideSaveBtn = false;
              }
              print zportfolio_theme_btn('add-custom-top-'.$sid, 'add-custom-top ' . $class, 'Add Item', $sid, true, true, $hideSaveBtn);

              if (!isset($section['items']))
                  $section['items'] = array();
              print zportfolio_theme_custom_item($section, $sid, $error, $years, $years_to, $months);
          ?>
      </div>
  </div>
</div>
<?php endforeach; ?>


<?php else: ?>
<div class="accordion-group accordion-group-custom accordion-group-custom-new<%= sid %>  new" data-type="6">
  <div class="accordion-heading">
    <div>
      <a class="custom-delete"></a>
      <a class="custom-rename"></a>
    </div>
      <a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#z-portfolio-control-group" href="#custom-new-<%= sid %>">
          <%= title %>
      </a>
      <input type="hidden" name="custom[new][<%= sid %>][title]" value="<%= title %>"/>
  </div>
  <div id="custom-new-<%= sid %>" class="accordion-body collapse">
      <div class="accordion-inner">
        <?php print $buttonTop ?>
        <?php print $button ?>
      </div>
  </div>
</div>
<?php endif;?>

