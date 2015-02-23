<input type="submit" class="btn btn-danger zportfolio-submit <?php print !empty($hideSaveBtn)?'hide':''; ?> <?php print (!empty($class) && $isTop)?$class:''; ?>" name="save"
    value="<?php print (empty($text))?t('Save'):t($text); ?>" />

