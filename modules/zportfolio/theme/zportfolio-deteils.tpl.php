<div class="row-fluid">
    <div class="span4">
        <label><?php print t('Your Name'); ?><span class="clr-red">*</span></label>
        <input type="text" name="name" value="<?php print $name; ?>" class="input-medium <?php isset($error['name'])?print 'error':''?>" id="z-name" required spellcheck="true" />
    </div>
    <div class="span4">
        <label><?php print t('Cell Phone'); ?><span class="clr-red">*</span></label>
        <input type="text" name="cellphone" value="<?php print $cellphone; ?>" class="input-medium <?php isset($error['cellphone'])?print 'error':''?>"
              id="z-phone" parsley-trigger="change" parsley-type="phone" required spellcheck="true" />
    </div>
    <div class="span4">
        <label><?php print t('Email'); ?><span class="clr-red">*</span></label>
        <input type="text" name="email" value="<?php print $email; ?>" class="input-medium <?php isset($error['email'])?print 'error':''?>"
               id="z-email" parsley-trigger="change" parsley-type="email" required spellcheck="true" />
    </div>
</div>
<div class="row-fluid">
    <div class="span12 address">
        <label><?php print t('Address'); ?><span class="clr-red">*</span></label>
        <textarea name="address" rows="2" class="autowraps <?php isset($error['address'])?print 'error':''?>" id="z-address" required spellcheck="true" ><?php print $address; ?></textarea>
    </div>
</div>
